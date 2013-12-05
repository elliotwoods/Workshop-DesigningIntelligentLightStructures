# Designing Intelligent Light Structures

* __Nantes__
* __4,5th December 2013__

https://github.com/elliotwoods/Workshop-DesigningIntelligentLightStructures/

## Principles

### Steps

0. Calibration
1. Scan
2. Decode
3. Triangulate
4. Animate

If you make changes to the model then you will need to perform steps 3 and 4 again (and often also 5).

If you move the camera or the projector, or make any focus or zoom changes.

## Setting up VVVV

Check inside the 'vvvv' folder of the workshop files, you will see a few zip's.

1. Unzip `vvvv_45beta31.2_x86.zip` to a location on your hard drive.
2. Open `addons_45beta31.2_x86.zip`, and drag the `addonpack` to inside your VVVV folder (next to vvvv.exe).
3. Open `vvvv-packs-dx11-b31.2-x86_1.zip` and drag the `packs` to inside your VVVV folder (next to vvvv.exe).
4. Unzip `VVVV.CV.zip` to be inside your new `packs` folder (e.g. `\vvvv_45beta31.2_x86\packs\VVVV.CV`).
5. Run `crack.exe` inside the vvvv folder, and make sure all the boxes are green (not red). If they are red then follow the instructions.
6. Run `vvvv.exe` and enjoy.

## 0. Calibrate Camera

Turn the lights on.

Grab a chessboard (either printed or on a screen). If you're using a paper chessboard, ensure it's backed onto a flat rigid surface (holding it in your hand is too floppy mate). The size (number of corners) and physical scale of your board don't matter too much, but make sure it's got square squares (not rectangles).

Open the `0. Calibrate Camera\main.v4p` patch.

Edit `Board Size x` and `Board Size y` to match your physical chessboard. The `Board Pitch` doesn't matter for calibrating the camera.

Make sure your camera isn't asleep and is attached via USB to your computer.

__NOTE : Now we're about to start calibrating, note that from now on, __you should not change the focus or zoom of your camera. So best get that setup now before continuing. Often it's a good idea to tape down the focus and zoom rings so that they will not be changed later by accident.__

Try hitting the `Shoot` button (right click): 

* Does it take a photo? If not, perhaps your camera is asleep, try waking it up and hit `Refresh` at the top left of your patch. You should see the name of your camera underneath the `Info` node.
* Does the photo appear on your computer screen? If not, then try restarting VVVV (perhaps you connected a projector to your computer since opening VVVV which will break the renderering). If this still doesn't work, then you may have to try a different computer, sorry :(.

__NOTE : Make sure to delete all existing camera calibration captures before starting the calibration. Click (LMB) on the word `open` to the left of `Output Folder`, this will bring up a folder of camera capture data, clear this folder of files before continuing__

Now try holding your chessboard in front of your camera, and hit `Shoot`, you should see the chessboard captured and VVVV should be drawing a red line over all the chessboard corners.


Try to capture the chessbaord in about 8 to 20 different positions.
Try to capture the chessboard in different corners of the camera image and different distances from the camera.

When you have enough captures, hit `Calibrate` (RMB). Scroll down and read the `Reprojection Error`. It should be something like 0.5 to 2px. If it's much larger than this, then start again. If not, continue on!

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
11. Set the camera to shoot to `L` JPEG format (not RAW, not JPEG + RAW).

#### Run scan software

Connect the DSLR to PC using USB cable. This can be on a USB extender if necessary.

Load up the main.v4p inside the `2. Scan` folder

Make sure the patch is seeing a camera (in Product Name under ListDevices). If not, make sure that the camera is not asleep, and is connected properly (and is a compatabile camera!). And try again.

Scroll down and hit `Go` (right click on the button).

Wait for the captures to finish.

Check the `Captures` folder, it should be full of images.