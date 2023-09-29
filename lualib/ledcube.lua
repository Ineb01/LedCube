LedCube = {
    empty =
    {{  
        {0,0,0},
        {0,0,0},
        {0,0,0}
    },{ 
        {0,0,0},
        {0,0,0},
        {0,0,0}
    },{
        {0,0,0},
        {0,0,0},
        {0,0,0}
    }},

    all =
    {{  
        {1,1,1},
        {1,1,1},
        {1,1,1}
    },{ 
        {1,1,1},
        {1,1,1},
        {1,1,1}
    },{
        {1,1,1},
        {1,1,1},
        {1,1,1}
    }}
}

function LedCube.sleep(a)
    local sec = tonumber(os.clock() + a); 
    while (os.clock() < sec) do
    end
end

function LedCube.rotate(ledState, times)
    for t=1,times,1
    do
        for i=1,3,1
        do
            tmp=ledState[i][1][1]
            ledState[i][1][1] = ledState[i][1][2]
            ledState[i][1][2] = ledState[i][1][3]
            ledState[i][1][3] = ledState[i][2][3]
            ledState[i][2][3] = ledState[i][3][3]
            ledState[i][3][3] = ledState[i][3][2]
            ledState[i][3][2] = ledState[i][3][1]
            ledState[i][3][1] = ledState[i][2][1]
            ledState[i][2][1] = tmp
        end
    end
end

function LedCube.shift(ledState, direction, times)
    for t=1,times,1
    do
        if direction=='up'
        then
            for i=1,3,1
            do
                for j=1,3,1
                do
                    tmp=ledState[3][i][j]
                    ledState[3][i][j]=ledState[2][i][j]
                    ledState[2][i][j]=ledState[1][i][j]
                    ledState[1][i][j]=tmp
                end
            end
        elseif direction=='down'
        then
            for i=1,3,1
            do
                for j=1,3,1
                do
                    tmp=ledState[1][i][j]
                    ledState[1][i][j]=ledState[2][i][j]
                    ledState[2][i][j]=ledState[3][i][j]
                    ledState[3][i][j]=tmp
                end
            end
        elseif direction=='back'
        then
            for i=1,3,1
            do
                for j=1,3,1
                do
                    tmp=ledState[i][1][j]
                    ledState[i][1][j]=ledState[i][2][j]
                    ledState[i][2][j]=ledState[i][3][j]
                    ledState[i][3][j]=tmp
                end
            end
        elseif direction=='forward'
        then
            for i=1,3,1
            do
                for j=1,3,1
                do
                    tmp=ledState[i][3][j]
                    ledState[i][3][j]=ledState[i][2][j]
                    ledState[i][2][j]=ledState[i][1][j]
                    ledState[i][1][j]=tmp
                end
            end
        elseif direction=='left'
        then
            for i=1,3,1
            do
                for j=1,3,1
                do
                    tmp=ledState[i][j][1]
                    ledState[i][j][1]=ledState[i][j][2]
                    ledState[i][j][2]=ledState[i][j][3]
                    ledState[i][j][3]=tmp
                end
            end
        elseif direction=='right'
        then
            for i=1,3,1
            do
                for j=1,3,1
                do
                    tmp=ledState[i][j][3]
                    ledState[i][j][3]=ledState[i][j][2]
                    ledState[i][j][2]=ledState[i][j][1]
                    ledState[i][j][1]=tmp
                end
            end
        end
    end
end

function LedCube.setLedCubeState(ledState)
    __internal__setLedCubeState(ledState);
end