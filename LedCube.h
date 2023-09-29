typedef struct 
{
    bool value;
} Led;

typedef struct 
{
    Led leds[3][3];
} LayerState;

typedef struct 
{
    bool setup;
} Control;

typedef struct
{
    Control c;
    LayerState layers[3];
} LedCubeState;


class LedCube
{
private:
    LedCubeState lcs;

public:
    LedCube();
    void setState(LedCubeState lcs);
    void render();
    LedCubeState getState() const { return lcs; }
};
