import numpy as np
import matplotlib.pyplot as plt
import pydicom
from os import walk
from stl import mesh
import plotly.graph_objects as go

def ij2XYZ(i, j, position, orientation, spacing):
    #see: https://nipy.org/nibabel/dicom/dicom_orientation.html
    initial_shape = i.shape

    # pixel_loc = [j ; i ; 0 ; 1] (already swapped i and j)
    pixel_loc = np.concatenate(
                    [
                        np.reshape(j, [-1,1]), 
                        np.reshape(i, [-1,1]),
                        np.reshape(j, [-1,1])*0,
                        np.reshape(j, [-1,1])*0+1,
                    ], 
                    axis=1
    ).T

    # transformation matrix
    M = np.array( 
        [
            [orientation[0]*spacing[0],     orientation[3]*spacing[1],      0,      position[0]],
            [orientation[1]*spacing[0],     orientation[4]*spacing[1],      0,      position[1]],
            [orientation[2]*spacing[0],     orientation[5]*spacing[1],      0,      position[2]],
            [0,                             0,                              0,      1],
        ]
    )

    # convert back from homogeneous to regular coords
    rcs_coord = np.dot(M, pixel_loc)
    rcs_coord = np.delete(rcs_coord, -1, axis=0)
    rcs_coord = rcs_coord.T

    X = np.reshape(rcs_coord[:,0], initial_shape)
    Y = np.reshape(rcs_coord[:,1], initial_shape)
    Z = np.reshape(rcs_coord[:,2], initial_shape)

    return X, Y, Z

# open STL file
stl_file = '/mnt/media/work/gradient/ICAD/prostate_samples/truth/cor0001a/t2_ax_0/cor0001a_t2_ax_0.wp.stl'
stl_mesh = mesh.Mesh.from_file(stl_file)

# open all DCM files in path
dcm_path = '/mnt/media/work/gradient/ICAD/prostate_samples/cor0001a/t2_ax_0/'
_, _, filenames = next(walk(dcm_path))
filenames.sort()
n_dcm = len(filenames)
dc = [pydicom.dcmread(dcm_path+f) for f in filenames]

# read important tags
slice_position = np.array([d[0x0020,0x0032].value for d in dc])
slice_orientation = np.array([d[0x0020,0x0037].value for d in dc])
slice_spacing = np.array([d[0x0028,0x0030].value for d in dc])
slice_image = np.array([d.pixel_array.astype(np.float32) for d in dc])

slc_i, slc_j = np.meshgrid(np.arange(256), np.arange(256), indexing='ij')

frames = []

slc_ind = 170
for k, slc_ind in enumerate(range(0, n_dcm, 5)):
    X, Y, Z = ij2XYZ(
        slc_i, 
        slc_j, 
        slice_position[slc_ind], 
        slice_orientation[slc_ind], 
        slice_spacing[slc_ind]
    )

    frames.append(
        go.Frame(
            data=go.Surface(
                x=X, 
                y=Y, 
                z=Z, 
                surfacecolor=np.flipud(slice_image[slc_ind]),
                showscale=False
            ),
            name=str(k)
        )
    )

fig = go.Figure(frames=frames)

X, Y, Z = ij2XYZ(
    slc_i, 
    slc_j, 
    slice_position[0], 
    slice_orientation[0], 
    slice_spacing[0]
)

# Add data to be displayed before animation starts
fig.add_trace(go.Surface(
                x=X, 
                y=Y, 
                z=Z, 
                surfacecolor=np.flipud(slice_image[0]),
                showscale=False
    )
)


fig.add_trace(        
        go.Scatter3d(
            x=stl_mesh.x.flatten(),
            y=stl_mesh.y.flatten(), 
            z=stl_mesh.z.flatten(),
            mode='markers'
        )
)

def frame_args(duration):
    return {
            "frame": {"duration": duration},
            "mode": "immediate",
            "fromcurrent": True,
            "transition": {"duration": duration, "easing": "linear"},
        }

sliders = [
            {
                "pad": {"b": 10, "t": 60},
                "len": 0.9,
                "x": 0.1,
                "y": 0,
                "steps": [
                    {
                        "args": [[f.name], frame_args(0)],
                        "label": str(k),
                        "method": "animate",
                    }
                    for k, f in enumerate(fig.frames)
                ],
            }
        ]

# Layout
fig.update_layout(
         title='Slices in volumetric data',
         width=1000,
         height=800,
         scene=dict(
                    xaxis=dict(range=[-100, 100], autorange=False),
                    yaxis=dict(range=[-100, 100], autorange=False),
                    zaxis=dict(range=[ -80, 150], autorange=False),
                    aspectratio=dict(x=1, y=1, z=1),
                    ),
         updatemenus = [
            {
                "buttons": [
                    {
                        "args": [None, frame_args(50)],
                        "label": "&#9654;", # play symbol
                        "method": "animate",
                    },
                    {
                        "args": [[None], frame_args(0)],
                        "label": "&#9724;", # pause symbol
                        "method": "animate",
                    },
                ],
                "direction": "left",
                "pad": {"r": 10, "t": 70},
                "type": "buttons",
                "x": 0.1,
                "y": 0,
            }
         ],
         sliders=sliders
)

fig.show()
