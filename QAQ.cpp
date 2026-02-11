#include <iostream>
using namespace std;
class IMotor {
	public:
		virtual void SetOutput(float output)=0;//设置输出：告诉电机用多少力（或电流）转动。
		virtual float GetSpeed()const=0;//读取反馈：询问电机当前转速是多少.
		virtual void Update()=0;//刷新状态：模拟电机内部的控制周期。
        virtual ~IMotor() = default;//虚析构函数
};
class DJIMotor :public IMotor {
public:
	void SetOutput(float output)override {
		printf("[CAN BUS] ID: 0x201, Send Current: %.1f\n", output);
	}
    float GetSpeed()const override {
        return 1000;
    }
    void Update()override {}
};

  class SimMotor : public IMotor {
   private:
         float velocity_;      // 当前速度
		 float outputForce_;   // 当前输入力
   public:
         void SetOutput(float output) override {
			 outputForce_ = output;
         }
         float GetSpeed() const override {
             return velocity_;
         }
         void Update() override {
             // 物理仿真：速度 = 旧速度 + (输入力 - 阻力)
             velocity_ = velocity_ + (outputForce_ - 0.1f * velocity_);
         }
        };
 void TestMotor(IMotor* motor) {
      motor->SetOutput(500);
      motor->Update();
      float speed = motor->GetSpeed();
	  printf("Motor Speed: %.2f\n", speed);
  }
 int main() {
     IMotor* dji = new DJIMotor();
     IMotor* sim = new SimMotor();

     TestMotor(dji);  
     TestMotor(sim);  
     delete dji;
     delete sim;
     return 0;
 }
