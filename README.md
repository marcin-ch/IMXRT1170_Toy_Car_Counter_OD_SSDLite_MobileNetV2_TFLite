# Overview
This is a counter of toy cars as example of object detection on i.MXRT1170 evaluation kit ([MIMXRT1170-EVK](https://www.nxp.com/design/development-boards/i-mx-evaluation-and-development-boards/i-mx-rt1170-evaluation-kit:MIMXRT1170-EVK)).

It is heavily based on [IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite) with following changes:
1. Model changed to [*Google Mobile Object Localizer*](https://tfhub.dev/google/lite-model/object_detection/mobile_object_localizer_v1/1/metadata/2):
    * a class-agnostic mobile model to localize objects in an image
    > note that this model supports only one class, i.e. each detection belongs to the same class
    * architecture: this model uses a MobileNet V2 backbone with a 0.75 width-multiplier, and a SSDLite detection head
    * [TFLite(v1, metadata)](https://tfhub.dev/google/lite-model/object_detection/mobile_object_localizer_v1/1/metadata/2?lite-format=tflite) version has been downloaded to */doc* folder
        * model name changed to *mobile_object_localizer_v1_1_meta.tflite*
    * **model prepared to use in embedded project** according to [Prepare object detection model and list of classes](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite#-prepare-object-detection-model-and-list-of-classes) and placed in */source/model* folder (*mobile_object_localizer_v1_1_meta.h*)
2. Images prepared in advance and placed in */doc* folder
    * *toy_cars_800x363_full_4x4.bmp*
    * *toy_cars_800x364_full_3x3.bmp*
    * *toy_cars_800x368_not_full_4x4.bmp*
    * *toy_cars_800x370_not_full_3x3.bmp*
    * above images have been extracted from original size 3968x2976 presenting whole shelf for toy cars and then resized to have 800 pixels in width
    * suffix *full* means that all cells are filled up with toy cars, *not_full* means that there are cells left blank
    * suffixes *4x4* and *3x3* mean how many cells have been presented in the image
    * **images prepared to use in embedded project** according to [Prepare example images to work on](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite#%EF%B8%8F-prepare-example-images-to-work-on) and placed in */source/image* folder 
3. Adjustments in code to use new model and images, changes can be tracked in following files:
    * [*/source/image/image_capture.c*](https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite/commit/76252d879cbb13668eac5d226a9ae3c593a94e4a#diff-0a384d564a6e5025813296b39cfb4ed3b6f8d471e0430efa9504d2a21485a26a)
    * [*/source/model/model_mobilenet_ops.cpp*](https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite/commit/76252d879cbb13668eac5d226a9ae3c593a94e4a#diff-a61013d371cbd3b88f54cd3169bba1c0eb5b857f65ecaacf199dcff3ca1a9d33)
    * [*/source/model/model.cpp*](https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite/commit/76252d879cbb13668eac5d226a9ae3c593a94e4a#diff-6d7188e06a96aa3c8fc97338e706c32605050da915dead69a9e2047c5239698d)
    * [*/source/demo_config.h*](https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite/commit/76252d879cbb13668eac5d226a9ae3c593a94e4a#diff-83c31c64110c9c3d1705e2620128217c027ba0a1ab7354286e5fac52d502a16f)
    * [*/source/demo_info.cpp*](https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite/commit/76252d879cbb13668eac5d226a9ae3c593a94e4a#diff-0ea1d52d61bc64a32711074f9aa944ef44a2899b518e88df2d083ca925114842)
    * [*/source/labels.h*](https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite/commit/76252d879cbb13668eac5d226a9ae3c593a94e4a#diff-37b5ace27c6a5267c86a43ebd67b9612150fde59ddfd9ad376ac1a54e693c7ce)

# Summary
| not fully equipped cell | fully equipped cell  | comments |
|----|----|----|
| ![imxrt1170_OD_resized_not_full_3x3.jpg](/doc/github_readme_images/imxrt1170_OD_resized_not_full_3x3.jpg) | ![imxrt1170_OD_resized_full_3x3.jpg](/doc/github_readme_images/imxrt1170_OD_resized_full_3x3.jpg) | cell 3x3, both detections are correct |
| ![imxrt1170_OD_resized_not_full_4x4.jpg](/doc/github_readme_images/imxrt1170_OD_resized_not_full_4x4.jpg) | ![imxrt1170_OD_resized_full_4x4.jpg](/doc/github_readme_images/imxrt1170_OD_resized_full_4x4.jpg) | cell 4x4, when fully equipped two objects have not been detected (`DETECTION_TRESHOLD` set to **19%**) |

Inference time is approximately **1,6 seconds** (connect terminal such as Tera Term to check it out), which is pretty great in comparison to similar repo [IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite) ([Summary](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite#summary) section) where inference time is 3,8 seconds. However, the models used between repos are different:
|  | model in this repo | model in compared [repo](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite) |
|----|----|----|
| inference time | 1,6 s | 3,8 s |
| input | 192x192 pixels | 300x300 pixels |
| detected classes | 1 | [90](https://www.tensorflow.org/lite/examples/object_detection/overview#fine-tuning_models_on_custom_data) |

The thing makes me wonder are scores [confidence % levels], they are pretty low, from 19% (because of `DETECTION_TRESHOLD` set to **19%**) up to only 73%, however in general they look like less than 50%. I believe this is for further investigation. Reviewing again the model's [documentation](https://tfhub.dev/google/object_detection/mobile_object_localizer_v1/1) (*Additional information* section), I figured out that recommended threshold is 0.2, therefore I was very close with setting `DETECTION_TRESHOLD` 19%. Perhaps, low scores might be totally fine as this is how this model works.

Model's [documentation](https://tfhub.dev/google/object_detection/mobile_object_localizer_v1/1) provides interesting info as follows:
* this model is suitable for localizing the **most prominent** objects in an image
* this model may not perform well on very small objects

**The goal of this repo is to choose another ready to use (out of the box) model coming from, for example [TensorFlow Hub](https://tfhub.dev/), and check how it influences inference time.**

## Remarks:
1. To choose particular image to test on, change `#define CURRENT_IMAGE` in *source/image/image_capture.c* to chosen one:
    ```c
    //#define CURRENT_IMAGE     toy_cars_800x364_full_3x3_bmp
    //#define CURRENT_IMAGE     toy_cars_800x370_not_full_3x3_bmp
    //#define CURRENT_IMAGE     toy_cars_800x368_not_full_4x4_bmp
    #define CURRENT_IMAGE     toy_cars_800x363_full_4x4_bmp
    ```

## How to use this repo (source code)
1. Clone the repo or download as *.zip* to your local disc drive
    * when clonning please use below command:
    ```console
    git clone https://github.com/marcin-ch/IMXRT1170_Toy_Car_Counter_OD_SSDLite_MobileNetV2_TFLite
    ```
2. Open **MCUXpresso**, you will be asked for choosing existing or creating new workspace, I recommend creating new workspace for testing purposes
3. From **QuickStart Panel** choose **Import project(s) from file system** and then select either unpacked repo (in case you clonned the repo) or zipped repo (in case you downloaded the archive)
4. Make sure **Copy projects into workspace** in **Options** is checked
5. Hit **Finish**
6. Select imported project in **Project Explorer** and hit **Debug** in **QuickStart Panel**, the application should be up and running
7. You can now remove clonned or downloaded repo, as it now exists in your workspace

## How to use this repo (binary file)
If you just want to check how the project looks like running on the board, you can flash binary file available in */doc/evkmimxrt1170_Toy_Car_Counter_OD_TFLite.bin* (there is another *.bin* available, *evkmimxrt1170_OD_TFLite.bin* and this is from original [repo](https://github.com/marcin-ch/IMXRT1170_Object_Detection_COCO_SSD_MobileNetV1_TFLite)). As i.MXRT1170 evaluation kit enumerates as MSD (Mass Storage Device) when connected to PC through USB cable, you can simply drag-n-drop binary file to your board. Wait few moments when flashing is in progress, reset the board and you should see application working.