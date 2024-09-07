// generated from file '/home/bill/src/Faust-DSP/chorus.dsp' by dsp2cc:
// Code generated with Faust 2.70.3 (https://faust.grame.fr)

#include <cmath>
#include <algorithm>

#define FAUSTFLOAT float

using std::signbit;

template<class T> inline T mydsp_faustpower2_f(T x) {return (x * x);}
template<class T> inline T mydsp_faustpower3_f(T x) {return ((x * x) * x);}
template<class T> inline T mydsp_faustpower4_f(T x) {return (((x * x) * x) * x);}
template<class T> inline T mydsp_faustpower5_f(T x) {return ((((x * x) * x) * x) * x);}
template<class T> inline T mydsp_faustpower6_f(T x) {return (((((x * x) * x) * x) * x) * x);}

#define always_inline inline __attribute__((__always_inline__))

typedef enum
{
   input0,
   input1,
   output0,
   output1,
   DELAY, // fHslider2 , 0.02, 0.0, 0.2, 0.01 
   DEPTH, // fHslider1 , 0.02, 0.0, 1.0, 0.01 
   FREQ, // fHslider0 , 3.0, 0.0, 1e+01, 0.01 
   LEVEL, // fHslider3 , 0.5, 0.0, 1.0, 0.01 
} PortIndex;


namespace chorus {
class mydspSIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec0[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, double* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iRec0[0] = iRec0[1] + 1;
			table[i1] = std::sin(9.587379924285257e-05 * double(iRec0[0] + -1));
			iRec0[1] = iRec0[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static double ftbl0mydspSIG0[65536];


class Dsp {
private:
	uint32_t fSampleRate;
	int IOTA0;
	double fVec0[131072];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT	*fHslider0_;
	double fConst1;
	double fRec1[2];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT	*fHslider1_;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT	*fHslider2_;
	double fRec2[2];
	double fConst2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT	*fHslider3_;
	double fVec1[131072];


public:
	void connect(uint32_t port,void* data);
	void del_instance(Dsp *p);
	void clear_state_f();
	void init(uint32_t sample_rate);
	void compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1);
	Dsp();
	~Dsp();
};



Dsp::Dsp() {
}

Dsp::~Dsp() {
}

inline void Dsp::clear_state_f()
{
	for (int l0 = 0; l0 < 131072; l0 = l0 + 1) fVec0[l0] = 0.0;
	for (int l2 = 0; l2 < 2; l2 = l2 + 1) fRec1[l2] = 0.0;
	for (int l3 = 0; l3 < 2; l3 = l3 + 1) fRec2[l3] = 0.0;
	for (int l4 = 0; l4 < 131072; l4 = l4 + 1) fVec1[l4] = 0.0;
}

inline void Dsp::init(uint32_t sample_rate)
{
	mydspSIG0* sig0 = newmydspSIG0();
	sig0->instanceInitmydspSIG0(sample_rate);
	sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
	deletemydspSIG0(sig0);
	fSampleRate = sample_rate;
	double fConst0 = std::min<double>(1.92e+05, std::max<double>(1.0, double(fSampleRate)));
	fConst1 = 1.0 / fConst0;
	fConst2 = 0.5 * fConst0;
	IOTA0 = 0;
	clear_state_f();
}

void always_inline Dsp::compute(int count, FAUSTFLOAT *input0, FAUSTFLOAT *input1, FAUSTFLOAT *output0, FAUSTFLOAT *output1)
{
#define fHslider0 (*fHslider0_)
#define fHslider1 (*fHslider1_)
#define fHslider2 (*fHslider2_)
#define fHslider3 (*fHslider3_)
	double fSlow0 = fConst1 * double(fHslider0);
	double fSlow1 = double(fHslider1);
	double fSlow2 = 0.0010000000000000009 * double(fHslider2);
	double fSlow3 = double(fHslider3);
	for (int i0 = 0; i0 < count; i0 = i0 + 1) {
		double fTemp0 = double(input0[i0]);
		fVec0[IOTA0 & 131071] = fTemp0;
		fRec1[0] = fSlow0 + (fRec1[1] - std::floor(fSlow0 + fRec1[1]));
		double fTemp1 = 65536.0 * (fRec1[0] - std::floor(fRec1[0]));
		double fTemp2 = std::floor(fTemp1);
		int iTemp3 = int(fTemp2);
		fRec2[0] = fSlow2 + 0.999 * fRec2[1];
		double fTemp4 = fConst2 * fRec2[0] * (fSlow1 * ((fTemp2 + (1.0 - fTemp1)) * ftbl0mydspSIG0[iTemp3 & 65535] + (fTemp1 - fTemp2) * ftbl0mydspSIG0[(iTemp3 + 1) & 65535]) + 1.0);
		int iTemp5 = int(fTemp4);
		double fTemp6 = std::floor(fTemp4);
		output0[i0] = FAUSTFLOAT(fTemp0 + fSlow3 * (fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp5))) & 131071] * (fTemp6 + (1.0 - fTemp4)) + (fTemp4 - fTemp6) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp5 + 1))) & 131071]));
		double fTemp7 = double(input1[i0]);
		fVec1[IOTA0 & 131071] = fTemp7;
		double fTemp8 = 65536.0 * (fRec1[0] + (0.25 - std::floor(fRec1[0] + 0.25)));
		double fTemp9 = std::floor(fTemp8);
		int iTemp10 = int(fTemp9);
		double fTemp11 = fConst2 * fRec2[0] * (fSlow1 * ((fTemp9 + (1.0 - fTemp8)) * ftbl0mydspSIG0[iTemp10 & 65535] + (fTemp8 - fTemp9) * ftbl0mydspSIG0[(iTemp10 + 1) & 65535]) + 1.0);
		int iTemp12 = int(fTemp11);
		double fTemp13 = std::floor(fTemp11);
		output1[i0] = FAUSTFLOAT(fTemp7 + fSlow3 * (fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp12))) & 131071] * (fTemp13 + (1.0 - fTemp11)) + (fTemp11 - fTemp13) * fVec1[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp12 + 1))) & 131071]));
		IOTA0 = IOTA0 + 1;
		fRec1[1] = fRec1[0];
		fRec2[1] = fRec2[0];
	}
#undef fHslider0
#undef fHslider1
#undef fHslider2
#undef fHslider3
}


void Dsp::connect(uint32_t port,void* data)
{
	switch ((PortIndex)port)
	{
	case DELAY: 
		fHslider2_ = static_cast<float*>(data); // , 0.02, 0.0, 0.2, 0.01 
		break;
	case DEPTH: 
		fHslider1_ = static_cast<float*>(data); // , 0.02, 0.0, 1.0, 0.01 
		break;
	case FREQ: 
		fHslider0_ = static_cast<float*>(data); // , 3.0, 0.0, 1e+01, 0.01 
		break;
	case LEVEL: 
		fHslider3_ = static_cast<float*>(data); // , 0.5, 0.0, 1.0, 0.01 
		break;
	default:
		break;
	}
}

Dsp *plugin() {
	return new Dsp();
}

void Dsp::del_instance(Dsp *p)
{
	delete p;
}
} // end namespace chorus
