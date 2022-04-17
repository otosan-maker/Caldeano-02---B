

#ifndef CAL_STATE
#define CAL_STATE

#define MODE_NUMBER  3
#define NUMERIC_MODE 1
#define ALPHA_MODE   2
#define SHIFT_MODE   3


class cal_state {
  public:
    cal_state();
    int Mode=NUMERIC_MODE;
  
};

#endif
