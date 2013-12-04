# Designing Intelligent Light Structures

__Notes__

## Principles

### Stages

0. Calibration
1. Scan
2. Decode
3. Triangulate
4. Animate

## Setting up VVVV

Check inside the 'vvvv' folder of the workshop files, you will see a few zip's.

1. Unzip `vvvv_45beta31.2_x86.zip` to a location on your hard drive.
2. Open `addons_45beta31.2_x86.zip`, and drag the `addonpack` to inside your VVVV folder (next to vvvv.exe).
3. Open `vvvv-packs-dx11-b31.2-x86_1.zip` and drag the `packs` to inside your VVVV folder (next to vvvv.exe).
4. Unzip `VVVV.CV.zip` to be inside your new `packs` folder (e.g. `\vvvv_45beta31.2_x86\packs\VVVV.CV`).
5. Run `crack.exe` inside the vvvv folder, and make sure all the boxes are green (not red). If they are red then follow the instructions.
6. Run `vvvv.exe` and enjoy.

## 0. Calibration

### Intention

Find 'Extrinsics' (relative pose of projector and camera).

Find 'Intrinsics' (shape of the view of projector and camera)

## 1. Scan

### Routine

#### Setup projector

1. Make projector white (e.g. drag a window fullscreen on the projector).
2. Zoom, pan and tilt to cover all the object you want to project onto (use the shadow to help you, don't worry about keeping the projector straight).
3. Focus the projector (focus 1/3 into your scene, you have 2x the depth of field behind the focal plane as in front).

#### Setup camera

0. Move the camera so that it can view the object (genearlly it should be 15 degrees angle away from the projector, further gives more resolution, but you're more likely to miss pixels which can't be seen by both the camera and projector).
1. Zoom, pan, tilt to cover the object
2. Turn on Auto-Focus (on the side of the lens switch AF/MF to AF).
3. Half press the shutter until beeps
4. Change back to Manual-Focus (MF).
5. Tape down the focus and zoom rings of the camera
6. Goto Manual Mode (M) on the function wheel.
7. Set shutter speed 1/20th of second (it will say 20)
8. Set the aperture to 22.
9. Set the ISO to 400
10. Take a test photo (fully press the shutter, make sure you can see light where the projection is and dark where it isn't). If it's too dark, then turn up the ISO (and too bright, turn down the ISO)

#### Run scan software

Connect the DSLR to PC using USB cable. This can be on a USB extender if necessary.

Load up the main.v4p inside the `2. Scan` folder

Make sure the patch is seeing a camera (in Product Name under ListDevices). If not, make sure that the camera is not asleep, and is connected properly (and is a compatabile camera!). And try again.

Scroll down and hit `Go` (right click on the button).

Wait for the captures to finish.

Check the `Captures` folder, it should be full of images.