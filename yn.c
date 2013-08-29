//
//  yn.c
//
//  Pure Data external for computation of
//  second kind Bessel functions yn(x)
//
//

#include "m_pd.h"
#include <math.h>

static t_class *yn_class;

typedef struct _yn {
  t_object  x_obj;
  t_float yn_order;
  double yn_input;
  double yn_output;
  t_inlet *f_in1;
  t_inlet *f_in2;
  t_outlet *f_out;
} t_yn;


void yn_float(t_yn *x, t_floatarg f)
{
  
  x->yn_input = (double)f;
  
  // compute first kind bessel with math.h function
  x->yn_output = yn((int) x->yn_order, x->yn_input);
  
  outlet_float(x->f_out, (t_float)x->yn_output);
  
  // post("Got value %f; order: %f; result: %f", f, x->yn_order, x->yn_output);
}

void yn_bang(t_yn *x)
{
  // bang outputs last result
  outlet_float(x->f_out, (t_float)x->yn_output);
}


void *yn_new(t_symbol *s, int argc, t_atom *argv)
{
  t_yn *x = (t_yn *)pd_new(yn_class);
  
  x->yn_input = 0.f;
  x->yn_output = 0.f;
  x->yn_order = 0;
  
  if (argc > 0)
  {
      x->yn_order = atom_getint(argv);
  }
  
  
  floatinlet_new (&x->x_obj, &x->yn_order);
  
  x->f_out = outlet_new(&x->x_obj, &s_float);
  
  return (void *)x;
}

void yn_setup(void) {
  
  yn_class = class_new(gensym("yn"),
                            (t_newmethod)yn_new,
                            0, sizeof(t_yn),
                            CLASS_DEFAULT,
                            A_GIMME, 0);
  
  class_addfloat (yn_class, yn_float);
  class_addbang  (yn_class, yn_bang);
  class_addmethod(yn_class,
                  (t_method)yn_float, gensym("float"), 0);
  
}
