
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cstring>
#include <unistd.h>

#include <lv2/core/lv2.h>
///////////////////////// MACRO SUPPORT ////////////////////////////////

#define PLUGIN_URI "urn:bill:chorus"

using std::min;
using std::max;

#define __rt_data __attribute__((section(".rt.data")))
#include "chorus.cc"

////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace chorus {

class Xchorus
{
private:
    float* input0;
    float* input1;
    float* output0;
    float* output1;
    chorus::Dsp* plugin;

    // private functions
    inline void run_dsp_(uint32_t n_samples);
    inline void connect_(uint32_t port,void* data);
    inline void init_dsp_(uint32_t rate);
    inline void connect_all__ports(uint32_t port, void* data);
    inline void activate_f();
    inline void clean_up();
    inline void deactivate_f();
public:
    // LV2 Descriptor
    static const LV2_Descriptor descriptor;
    // static wrapper to private functions
    static void deactivate(LV2_Handle instance);
    static void cleanup(LV2_Handle instance);
    static void run(LV2_Handle instance, uint32_t n_samples);
    static void activate(LV2_Handle instance);
    static void connect_port(LV2_Handle instance, uint32_t port, void* data);
    static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
    Xchorus();
    ~Xchorus();
};

// constructor
Xchorus::Xchorus() :

    input0(NULL),
    input1(NULL),
    output0(NULL),
    output1(NULL),
    plugin(chorus::plugin()) {};

// destructor
Xchorus::~Xchorus() {
    plugin->del_instance(plugin);
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Xchorus::init_dsp_(uint32_t rate)
{
    plugin->init(rate);
}

// connect the Ports used by the plug-in class
void Xchorus::connect_(uint32_t port,void* data)
{
    switch ((PortIndex)port)
    {
        case 0:
            input0 = static_cast<float*>(data);
            break;
        case 1:
            input1 = static_cast<float*>(data);
            break;
        case 2:
            output0 = static_cast<float*>(data);
            break;
        case 3:
            output1 = static_cast<float*>(data);
            break;
        default:
            break;
    }
}

void Xchorus::activate_f()
{
    // allocate the internal DSP mem
}

void Xchorus::clean_up()
{
    // delete the internal DSP mem
}

void Xchorus::deactivate_f()
{
    // delete the internal DSP mem
}

void Xchorus::run_dsp_(uint32_t n_samples)
{
    if(n_samples<1) return;


    // do inplace processing on default
    if(output0 != input0)
        memcpy(output0, input0, n_samples*sizeof(float));


    // do inplace processing on default
    if(output1 != input1)
        memcpy(output1, input1, n_samples*sizeof(float));

    plugin->compute(n_samples, output1, output1);
}

void Xchorus::connect_all__ports(uint32_t port, void* data)
{
    // connect the Ports used by the plug-in class
    connect_(port,data); 
    plugin->connect(port,data);}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Xchorus::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
    // init the plug-in class
    Xchorus *self = new Xchorus();
    if (!self) {
        return NULL;
    }
    self->init_dsp_((uint32_t)rate);
    return (LV2_Handle)self;
}

void Xchorus::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
    // connect all ports
    static_cast<Xchorus*>(instance)->connect_all__ports(port, data);
}

void Xchorus::activate(LV2_Handle instance)
{
    // allocate needed mem
    static_cast<Xchorus*>(instance)->activate_f();
}

void Xchorus::run(LV2_Handle instance, uint32_t n_samples)
{
    // run dsp
    static_cast<Xchorus*>(instance)->run_dsp_(n_samples);
}

void Xchorus::deactivate(LV2_Handle instance)
{
    // free allocated mem
    static_cast<Xchorus*>(instance)->deactivate_f();
}

void Xchorus::cleanup(LV2_Handle instance)
{
    // well, clean up after us
    Xchorus* self = static_cast<Xchorus*>(instance);
    self->clean_up();
    delete self;
}

const LV2_Descriptor Xchorus::descriptor =
{
    PLUGIN_URI ,
    Xchorus::instantiate,
    Xchorus::connect_port,
    Xchorus::activate,
    Xchorus::run,
    Xchorus::deactivate,
    Xchorus::cleanup,
    NULL
};

} // end namespace chorus

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
    switch (index)
    {
        case 0:
            return &chorus::Xchorus::descriptor;
        default:
            return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
