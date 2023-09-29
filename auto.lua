require "lualib.ledcube"

ledState = 
{{  
    {0,1,0},
    {0,0,0},
    {0,0,0}
},{
    {0,1,0},
    {0,0,0},
    {0,0,0}
},{
    {0,1,0},
    {0,0,0},
    {0,0,0}
}}

LedCube.setLedCubeState(LedCube.empty)
LedCube.sleep(.5);

for i=1,50,1
do
    LedCube.setLedCubeState(ledState);
    LedCube.rotate(ledState, 1);
    LedCube.sleep(.1);
end

