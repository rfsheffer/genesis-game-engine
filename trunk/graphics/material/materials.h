//
//  materials.h
//  Materials Library.
//
//  Created by Ryan Sheffer on 2012-12-17.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MATERIALS_H
#define MATERIALS_H

class CMaterials
{
public:
    
    // Loading and unloading
    bool LoadTexture(const char *pszTextureName);
    bool UnloadTexture(const char *pszTextureName);
    void UnloadAllTextures(void);
    void RefreshAllMaterials(void);
    
    bool IsTextureLoaded(const char *pszTextureName);
    
    
private:
    
};


#endif // MATERIALS_H
