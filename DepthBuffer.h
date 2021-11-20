#ifndef DEPTH_BUFFER_T
#define DEPTH_BUFFER_T 1
class DepthBuffer {
  public:
    DepthBuffer(int width, int height);
    ~DepthBuffer();
    float getDepth(int i, int j);
    void setDepth(int i, int j, float depth);
  
  private:
    int myWidth;
    int myHeight;
    float* myDepths;
};
#endif