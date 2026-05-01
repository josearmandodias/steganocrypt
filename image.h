#ifndef IMAGE_H
#define IMAGE_H

sImagePPM* charger_ppm(const char* chemin);        
int        sauvegarder_ppm(const sImagePPM*, const char*);   
void       liberer_ppm(sImagePPM* img);

#endif 