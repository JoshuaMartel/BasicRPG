#pragma once
#include "Button.h"
#include "ButtonType.h"

class ExitButton :
    public Button
{
public:
    ExitButton();

    ButtonType type();
private:
    ButtonType m_type;
};

