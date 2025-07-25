/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDHEAPBASE_HPP
#define FRONTENDHEAPBASE_HPP

#include <common/Meta.hpp>
#include <common/Partition.hpp>
#include <mvp/MVPHeap.hpp>

#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/Model.hpp>

#include <gui/screen_1_screen/Screen_1View.hpp>
#include <gui/screen_1_screen/Screen_1Presenter.hpp>
#include <gui/screen_1_statistics_screen/Screen_1_StatisticsView.hpp>
#include <gui/screen_1_statistics_screen/Screen_1_StatisticsPresenter.hpp>
#include <gui/screen_1_lp_statistics_screen/Screen_1_LP_StatisticsView.hpp>
#include <gui/screen_1_lp_statistics_screen/Screen_1_LP_StatisticsPresenter.hpp>
#include <gui/screen_2_screen/Screen_2View.hpp>
#include <gui/screen_2_screen/Screen_2Presenter.hpp>
#include <gui/screen_2_pm2_screen/Screen_2_PM2View.hpp>
#include <gui/screen_2_pm2_screen/Screen_2_PM2Presenter.hpp>
#include <gui/screen_2_pm0_screen/Screen_2_PM0View.hpp>
#include <gui/screen_2_pm0_screen/Screen_2_PM0Presenter.hpp>
#include <gui/screen_3_lt_screen/Screen_3_LTView.hpp>
#include <gui/screen_3_lt_screen/Screen_3_LTPresenter.hpp>


/**
 * This class provides the memory that shall be used for memory allocations
 * in the frontend. A single instance of the FrontendHeap is allocated once (in heap
 * memory), and all other frontend objects such as views, presenters and data model are
 * allocated within the scope of this FrontendHeap. As such, the RAM usage of the entire
 * user interface is sizeof(FrontendHeap).
 *
 * @note The FrontendHeap reserves memory for the most memory-consuming presenter and
 * view only. The largest of these classes are determined at compile-time using template
 * magic. As such, it is important to add all presenters, views and transitions to the
 * type lists in this class.
 *
 */
class FrontendHeapBase : public touchgfx::MVPHeap
{
public:
    /**
     * A list of all view types. Must end with meta::Nil.
     * @note All view types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< Screen_1View,
            touchgfx::meta::TypeList< Screen_1_StatisticsView,
            touchgfx::meta::TypeList< Screen_1_LP_StatisticsView,
            touchgfx::meta::TypeList< Screen_2View,
            touchgfx::meta::TypeList< Screen_2_PM2View,
            touchgfx::meta::TypeList< Screen_2_PM0View,
            touchgfx::meta::TypeList< Screen_3_LTView,
            touchgfx::meta::Nil > > > > > >
            > GeneratedViewTypes;

    /**
     * Determine (compile time) the View type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedViewTypes >::type MaxGeneratedViewType;

    /**
     * A list of all presenter types. Must end with meta::Nil.
     * @note All presenter types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< Screen_1Presenter,
            touchgfx::meta::TypeList< Screen_1_StatisticsPresenter,
            touchgfx::meta::TypeList< Screen_1_LP_StatisticsPresenter,
            touchgfx::meta::TypeList< Screen_2Presenter,
            touchgfx::meta::TypeList< Screen_2_PM2Presenter,
            touchgfx::meta::TypeList< Screen_2_PM0Presenter,
            touchgfx::meta::TypeList< Screen_3_LTPresenter,
            touchgfx::meta::Nil > > > > > >
            > GeneratedPresenterTypes;

    /**
     * Determine (compile time) the Presenter type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedPresenterTypes >::type MaxGeneratedPresenterType;

    /**
     * A list of all transition types. Must end with meta::Nil.
     * @note All transition types used in the application MUST be added to this list!
     */
    typedef touchgfx::meta::TypeList< touchgfx::NoTransition,
            touchgfx::meta::Nil
            > GeneratedTransitionTypes;

    /**
     * Determine (compile time) the Transition type of largest size.
     */
    typedef touchgfx::meta::select_type_maxsize< GeneratedTransitionTypes >::type MaxGeneratedTransitionType;

    virtual void gotoStartScreen(FrontendApplication& app)
    {
        app.gotoScreen_1ScreenNoTransition();
    }
protected:
    FrontendHeapBase(touchgfx::AbstractPartition& presenters, touchgfx::AbstractPartition& views, touchgfx::AbstractPartition& transitions, FrontendApplication& app)
        : MVPHeap(presenters, views, transitions, app)
    {

    }

};

#endif // FRONTENDHEAPBASE_HPP
