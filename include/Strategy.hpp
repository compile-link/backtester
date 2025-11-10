#pragma once

class Strategy {
    public:
        virtual double signal() = 0; 
        virtual ~Strategy() = default;
    };