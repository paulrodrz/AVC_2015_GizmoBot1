#ifndef WHEEL_ENCODER_H
#define WHEEL_ENCODER_H

#define WHEEL_LEFT_PIN 2
#define WHEEL_RIGHT_PIN 3

#define COUNTS_PER_ROTATION 15.0
#define MM_PER_ROTATION 249.4424567
#define MM_PER_COUNT (MM_PER_ROTATION / COUNTS_PER_ROTATION)

class WheelEncoder {
  public:
    WheelEncoder() {
      reset();
    };
    
    ~WheelEncoder() {};

    void leftInc() {
      wheelLeftCount++;
    }

    void rightInc() {
      wheelRightCount++;
    }

    void reset() {
      wheelLeftCount=0;
      wheelRightCount=0;
      left=0;
      right=0;
    };
    
    void update() {
      left=wheelLeftCount;
      right=wheelRightCount;

      // Subtract off last readings
      wheelLeftCount-=left;  
      wheelRightCount-=right;
    };
    
    float getForwardDistance() {
      return right*MM_PER_COUNT;
    };
    
    float getHorizontalDistance() {
    };

  private:
    volatile uint16_t wheelLeftCount;
    volatile uint16_t wheelRightCount;

    uint16_t left;
    uint16_t right;
};

#endif //WHEEL_ENCODER_H
