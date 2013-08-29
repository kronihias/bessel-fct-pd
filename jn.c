//
//  jn.c
//
//  Pure Data external for computation of
//  first kind Bessel functions Jn(x)
//
//

#include "m_pd.h"
#include <math.h>

static t_class *jn_class;

typedef struct _jn {
  t_object  x_obj;
  t_float jn_order;
  double jn_input;
  double jn_output;
  t_inlet *f_in1;
  t_inlet *f_in2;
  t_outlet *f_out;
} t_jn;


void jn_float(t_jn *x, t_floatarg f)
{
  
  x->jn_input = (double)f;
  
  // compute first kind bessel with math.h function
  x->jn_output = jn((int) x->jn_order, x->jn_input);
  
  outlet_float(x->f_out, (t_float)x->jn_output);
  
  // post("Got value %f; order: %f; result: %f", f, x->jn_order, x->jn_output);
}

void jn_bang(t_jn *x)
{
  // bang outputs last result
  outlet_float(x->f_out, (t_float)x->jn_output);
}


void *jn_new(t_symbol *s, int argc, t_atom *argv)
{
  t_jn *x = (t_jn *)pd_new(jn_class);
  
  x->jn_input = 0.f;
  x->jn_output = 0.f;
  x->jn_order = 0;
  
  if (argc > 0)
  {
      x->jn_order = atom_getint(argv);
  }
  
  
  floatinlet_new (&x->x_obj, &x->jn_order);
  
  x->f_out = outlet_new(&x->x_obj, &s_float);
  
  return (void *)x;
}

void jn_setup(void) {
  
  jn_class = class_new(gensym("jn"),
                            (t_newmethod)jn_new,
                            0, sizeof(t_jn),
                            CLASS_DEFAULT,
                            A_GIMME, 0);
  
  class_addfloat (jn_class, jn_float);
  class_addbang  (jn_class, jn_bang);
  class_addmethod(jn_class,
                  (t_method)jn_float, gensym("float"), 0);
  
}
