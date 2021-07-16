#pragma once

class DancingNode{
    private:
        DancingNode* up, *down, *left, *right;

    public:
        DancingNode(){ up = down = left = right = this;}
};