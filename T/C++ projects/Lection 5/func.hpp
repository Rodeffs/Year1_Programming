//
// Created by Администратор on 05.10.2022.
//


#ifndef LECTION_5_FUNC_HPP
#define LECTION_5_FUNC_HPP

#endif //LECTION_5_FUNC_HPP

#pragma once // !!! Подключать файл можно только ОДИН раз

namespace myNS { // Можно создавать своё пространство имён
    int cout (int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }
}