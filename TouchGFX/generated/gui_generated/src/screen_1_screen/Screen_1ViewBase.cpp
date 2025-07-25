/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen_1_screen/Screen_1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen_1ViewBase::Screen_1ViewBase()
{
    __background.setPosition(0, 0, 272, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    Logo_BG.setXY(0, 0);
    Logo_BG.setBitmap(touchgfx::Bitmap(BITMAP_BG_ID));
    add(Logo_BG);

    EV_Text.setPosition(127, 124, 40, 15);
    EV_Text.setColor(touchgfx::Color::getColorFromRGB(193, 207, 221));
    EV_Text.setLinespacing(0);
    Unicode::snprintf(EV_TextBuffer, EV_TEXT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_JNFW).getText());
    EV_Text.setWildcard(EV_TextBuffer);
    EV_Text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GAAU));
    add(EV_Text);

    Banner.setXY(0, 0);
    Banner.setBitmap(touchgfx::Bitmap(BITMAP_SCREEN_1_ID));
    add(Banner);

    ER_Text.setPosition(65, 123, 62, 12);
    ER_Text.setColor(touchgfx::Color::getColorFromRGB(193, 207, 221));
    ER_Text.setLinespacing(0);
    ER_Text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_YYMQ));
    add(ER_Text);

    Bar_Text_0.setXY(158, 80);
    Bar_Text_0.setColor(touchgfx::Color::getColorFromRGB(193, 207, 221));
    Bar_Text_0.setLinespacing(0);
    Bar_Text_0.setTypedText(touchgfx::TypedText(T___SINGLEUSE_OS4M));
    add(Bar_Text_0);

    Bar_Text_0_10.setXY(253, 80);
    Bar_Text_0_10.setColor(touchgfx::Color::getColorFromRGB(193, 207, 221));
    Bar_Text_0_10.setLinespacing(0);
    Bar_Text_0_10.setTypedText(touchgfx::TypedText(T___SINGLEUSE_JU2A));
    add(Bar_Text_0_10);

    Kev_Text.setPosition(167, 124, 62, 12);
    Kev_Text.setColor(touchgfx::Color::getColorFromRGB(193, 207, 221));
    Kev_Text.setLinespacing(0);
    Kev_Text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_J2TV));
    add(Kev_Text);

    PC_Text.setPosition(10, 97, 144, 13);
    PC_Text.setColor(touchgfx::Color::getColorFromRGB(193, 207, 221));
    PC_Text.setLinespacing(0);
    PC_Text.setTypedText(touchgfx::TypedText(T___SINGLEUSE_HC5R));
    add(PC_Text);

    PC_Progress.setXY(161, 100);
    PC_Progress.setProgressIndicatorPosition(0, 0, 100, 10);
    PC_Progress.setRange(0, 8680);
    PC_Progress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    PC_Progress.setBackground(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BOXPROGRESS_NORMAL_TINY_ID));
    PC_Progress.setColor(touchgfx::Color::getColorFromRGB(255, 114, 118));
    PC_Progress.setValue(8680);
    add(PC_Progress);
}

Screen_1ViewBase::~Screen_1ViewBase()
{

}

void Screen_1ViewBase::setupScreen()
{
    transitionBegins();
}

void Screen_1ViewBase::changeScreenRight()
{
    //changeScreenRightInt
    //When changeScreenRight is called change screen to Screen_2
    //Go to Screen_2 with no screen transition
    application().gotoScreen_2ScreenNoTransition();
}

void Screen_1ViewBase::handleTickEvent()
{
    //updateEventsInt
    //When every N tick call virtual function
    //Call updateEvents
    updateEvents();

    //checkI2CStatusInt
    //When every N tick call virtual function
    //Call checkI2CStatus
    checkI2CStatus();
}

void Screen_1ViewBase::changeScreenDown()
{
    //changeScreenDownInt
    //When changeScreenDown is called change screen to Screen_1_Statistics
    //Go to Screen_1_Statistics with no screen transition
    application().gotoScreen_1_StatisticsScreenNoTransition();
}

void Screen_1ViewBase::transitionBegins()
{
    //screenInitInt
    //When screen transition begins call virtual function
    //Call screenInit
    screenInit();
}
