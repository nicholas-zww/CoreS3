#include "ResourcePool.h"
#include "ResourceManager.h"

static ResourceManager Font_;
static ResourceManager Image_;
static ResourceManager Wav_;

extern "C" {
#define IMPORT_FONT(name)                       \
    do {                                        \
        LV_FONT_DECLARE(name)                   \
        Font_.AddResource(#name, (void*)&name); \
    } while (0)

#define IMPORT_IMG(name)                         \
    do {                                         \
        LV_IMG_DECLARE(name)                     \
        Image_.AddResource(#name, (void*)&name); \
    } while (0)

#define IMPORT_WAV(name, size)                 \
    do {                                       \
        extern const unsigned char name[size]; \
        Wav_.AddResource(#name, (void*)&name); \
    } while (0)

static void Resource_Init() {
    /* Import Fonts */
    IMPORT_FONT(ubuntu_mono_8);
    IMPORT_FONT(alibaba_pht_26);

    /* Import Images */
    // IMPORT_IMG(app_i2c_internal);
 
    /* Import WAV */
    IMPORT_WAV(poweron_2_5s, 441538);
    IMPORT_WAV(select_0_5s, 88738);
}

} /* extern "C" */

void ResourcePool::Init() {
    Resource_Init();
    Font_.SetDefault((void*)LV_FONT_DEFAULT);
}

lv_font_t* ResourcePool::GetFont(const char* name) {
    return (lv_font_t*)Font_.GetResource(name);
}
const void* ResourcePool::GetImage(const char* name) {
    return Image_.GetResource(name);
}
const void* ResourcePool::GetWav(const char* name) {
    return Wav_.GetResource(name);
}
