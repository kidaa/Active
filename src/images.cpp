// Simple example for EffectMixer. Mixers let you run multiple effects, and they
// handle concurrent rendering on multiple CPU cores.

#include "lib/effect_runner.h"
#include "lib/effect_mixer.h"
#include "lib/tinydir.h"

#include "images.h"
#include "particle_trail.h"
#include "rings.h"

int main(int argc, char **argv)
{
    tinydir_dir dir;
    if (tinydir_open(&dir, "/Users/matt//active/video/queue/") == -1)
    {
        perror("Error opening file");
            tinydir_close(&dir);
            return 0;
    }

    EffectMixer mixer;

    ImageEffect * tmpImage;


    int imageIndex = 0;
    int maxImageIndex = 150;


    while (dir.has_next) {
        tinydir_file file;
        if (tinydir_readfile(&dir, &file) == -1)
        {
            perror("Error getting file");
             tinydir_close(&dir);
            return 0;
        }

        printf("%s", file.name);
        if (file.is_dir)
        {
            printf("/");
        } 
        printf("\n");

        if (maxImageIndex > imageIndex) {
            if (!strcmp(file.extension, "png")) {
                printf("found image %s\n", file.name);
                /*
                printf("Path: %s\nName: %s\nExtension: %s\nIs dir? %s\nIs regular file? %s\n",
                file.path, file.name, file.extension,
                file.is_dir?"yes":"no", file.is_reg?"yes":"no");
                */

                tmpImage = new ImageEffect(file.path);
              //  DotEffect e("data/dot.png");
              //  img[imageIndex] = tmpImage;
              //  mixer.add(img[imageIndex]);
                mixer.add(tmpImage);
              //  imageIndex++;
            }
        }

        tinydir_next(&dir);
    }

          
    EffectRunner r;
    r.setEffect(&mixer);
    r.setMaxFrameRate(30);

    r.setLayout("../../../Active/layout/layout-60x24.json");
    if (!r.parseArguments(argc, argv)) {
        return 1;
    }

    float state = 0;

    while (true) {
        EffectRunner::FrameStatus frame = r.doFrame();
        const float speed = 10.0f; //FAST
       // const float speed = 0.001f; //SLOW

/*
       // Animate the mixer's fader controls
        state = fmod(state + frame.timeDelta * speed, 2 * M_PI);
        for (int i = 0; i < mixer.numChannels(); i++) {
            float theta = state + i * (2 * M_PI) / mixer.numChannels();
            mixer.setFader(i, std::max(0.0f, sinf(theta)));
        }

        */

        // Animate the mixer's fader controls
  ///*
        state = fmod(state + frame.timeDelta * speed, mixer.numChannels());
        for (int i = 0; i < mixer.numChannels(); i++) {

            mixer.setFader(i, 0.0);

            //float remainder = state - i;
            // is this state
            if ( i == (int)state) {
                mixer.setFader(i, 1.0);
            }

       /*     // is next state
            int nextState = (int) state;
            nextState += 1;
            nextState % mixer.numChannels();
            if (i == nextState) {
                mixer.setFader(i, 1-remainder);
            }
*/
     //       float theta = state + i * (2 * M_PI) / mixer.numChannels();
      //      mixer.setFader(i, std::max(0.0f, sinf(theta)));
        }
      //  */

        // Main loops and Effects can both generate verbose debug output (-v command line option)
        if (frame.debugOutput) {
            fprintf(stderr, "\t[main] state = %f\n", state);
        }
    }



}