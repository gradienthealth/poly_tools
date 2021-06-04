import numpy as np
import matplotlib.pyplot as plt
import pydicom
from os import walk
from stl import mesh
import plotly.graph_objects as go

def get_tform(N, position_first, position_last, orientation, spacing):
    # transformation matrix
    M = np.array( 
        [
            [orientation[0]*spacing[0],     orientation[3]*spacing[1],  (position_last[0] - position_first[0])/(N-1),   position_first[0]],
            [orientation[1]*spacing[0],     orientation[4]*spacing[1],  (position_last[1] - position_first[1])/(N-1),   position_first[1]],
            [orientation[2]*spacing[0],     orientation[5]*spacing[1],  (position_last[2] - position_first[2])/(N-1),   position_first[2]],
            [0,                             0,                          0,                                              1],
        ]
    )
    return M

def ijk2XYZ(i, j, k, M):

    initial_shape = i.shape

    # pixel_loc = [j ; i ; k ; 1] (already swapped i and j)
    pixel_loc = np.concatenate(
                    [
                        np.reshape(j, [-1,1]), 
                        np.reshape(i, [-1,1]),
                        np.reshape(k, [-1,1]),
                        np.ones_like(np.reshape(k, [-1,1])),
                    ], 
                    axis=1
    ).T

    # convert back from homogeneous to regular coords
    rcs_coord = np.dot(M, pixel_loc)
    rcs_coord = np.delete(rcs_coord, -1, axis=0)
    rcs_coord = rcs_coord.T

    X = np.reshape(rcs_coord[:,0], initial_shape)
    Y = np.reshape(rcs_coord[:,1], initial_shape)
    Z = np.reshape(rcs_coord[:,2], initial_shape)

    return X, Y, Z

# open STL file
stl_file = '/mnt/media/work/gradient/ICAD/prostate_samples/truth/cor0004a/t2_ax_0/cor0004a_t2_ax_0.cg.stl'
stl_mesh = mesh.Mesh.from_file(stl_file)

# open all DCM files in path
dcm_path = '/mnt/media/work/gradient/ICAD/prostate_samples/cor0004a/t2_ax_0/'
_, _, filenames = next(walk(dcm_path))
filenames.sort()
n_dcm = len(filenames)
dc = [pydicom.dcmread(dcm_path+f) for f in filenames]

# read important tags
slice_position = np.array([d[0x0020,0x0032].value for d in dc])
slice_orientation = np.array([d[0x0020,0x0037].value for d in dc])
slice_spacing = np.array([d[0x0028,0x0030].value for d in dc])
slice_image = np.array([d.pixel_array.astype(np.float32) for d in dc])
slice_location = np.array([d[0x0020,0x1041].value for d in dc])

M = get_tform(n_dcm, slice_position[0], slice_position[-1], slice_orientation[0], slice_spacing[0])

frames = []
slc_ind = 170
for k, slc_ind in enumerate(range(0, n_dcm, 5)):
    slc_i, slc_j, slc_k = np.meshgrid(np.arange(256), np.arange(256), slc_ind, indexing='ij')
    X, Y, Z = ijk2XYZ(
        slc_i, 
        slc_j, 
        slc_k,
        M
    )

    frames.append(
        go.Frame(
            data=go.Surface(
                x=np.squeeze(X),
                y=np.squeeze(Y), 
                z=np.squeeze(Z), 
                surfacecolor=slice_image[slc_ind],
                opacity=0.75,
                showscale=False,
            ),
            name=str(k)
        )
    )

fig = go.Figure(frames=frames)

slc_i, slc_j, slc_k = np.meshgrid(np.arange(256), np.arange(256), 0, indexing='ij')
X, Y, Z = ijk2XYZ(
    slc_i, 
    slc_j, 
    slc_k,
    M
)

# Add data to be displayed before animation starts
fig.add_trace(go.Surface(
                x=np.squeeze(X), 
                y=np.squeeze(Y), 
                z=np.squeeze(Z), 
                surfacecolor=slice_image[0],
                showscale=False
    )
)


M = get_tform(n_dcm, slice_position[0], slice_position[-1], slice_orientation[0], slice_spacing[0])

fig.add_trace(        
        go.Scatter3d(
            x=stl_mesh.x.flatten(),
            y=stl_mesh.y.flatten(), 
            z=stl_mesh.z.flatten(),
            mode='markers',
            marker=dict(
                size=1,
                opacity=0.5
            )
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
                    xaxis=dict(range=[-200, 200], autorange=False),
                    yaxis=dict(range=[-200, 200], autorange=False),
                    zaxis=dict(range=[-200, 200], autorange=False),
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
