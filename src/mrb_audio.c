#include <mrgss.h>
#include <soloud_c.h>

static const struct mrb_data_type audio_data_type = {
  "MRGSS::Point", mrb_free
};

static Soloud* soloud;

static mrb_value initialize(mrb_state *mrb, mrb_value self) {   
    char* filename;
    mrb_get_args(mrb, "z", &filename);
   
     soloud = Soloud_create();
     Soloud_init(soloud);
     WavStream *stream = WavStream_create();
    if (WavStream_load(stream, filename)){
        Soloud_play(soloud, stream);
    } else {
        printf("fallo el cargado del archivo: %s", filename);
        WavStream_destroy(stream);
    }
    return self;
}

static mrb_value play(mrb_state *mrb, mrb_value self) {

    return self;
}

void create_audio_type(mrb_state* mrb) {
    struct RClass* type = mrgss_class_new(mrb, "Audio");
    mrb_define_method(mrb, type, "initialize", initialize, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, type, "play", play, MRB_ARGS_REQ(1));
}