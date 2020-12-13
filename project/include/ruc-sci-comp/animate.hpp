#pragma once
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <numeric>
#include <string>
#include <vector>
#include <malen/bokeh.h>
#include <ruc-sci-comp/serialize.hpp>


const char *DISABLE_MALEN = getenv("DISABLE_MALEN");


void animate(std::vector<std::vector<std::vector<int>>> &data)
{
    serialize(data);

    std::string flag = DISABLE_MALEN == nullptr ? "ENABLE" : DISABLE_MALEN;
    if (flag.empty())
    {
        return;
    }

    setenv("PYTHONPATH", ".:..:../..", 1);
    malen::Bokeh mb;

    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    for (auto &frame : data)
    {
        std::reverse(std::begin(frame), std::end(frame));

        for (const auto &row : frame)
        {
            auto r = std::minmax_element(begin(row), end(row));
            min = *r.first < min ? *r.first : min;
            max = *r.second > max ? *r.second : max;
        }
    }

    auto size = data[0].size();
    auto match_aspect = malen::kwarg("match_aspect", true);
    auto x_range = malen::kwarg("x_range", std::vector<int>{0,static_cast<int>(size)});
    auto y_range = malen::kwarg("y_range", std::vector<int>{0,static_cast<int>(size)});

    auto *figure = mb.make_new_figure("Abelian Sandpile Model", match_aspect, x_range, y_range);

    auto ticker = mb.ticker("BasicTicker");
    auto color_mapper = mb.color_mapper("LinearColorMapper",
        malen::kwarg("palette", "Spectral11"),
        malen::kwarg("low", 0),
        malen::kwarg("high", max)
    );
    mb.color_bar(figure,
        malen::kwarg("color_mapper", color_mapper),
        malen::kwarg("ticker", ticker),
        malen::kwarg("location", std::vector<int>{0,0})
    );

    auto im = mb.image(figure,
        data[0], malen::kwarg("color_mapper", color_mapper)
    );

    auto slider = mb.slider(im, "Frame", 0, data.size()-1, malen::kwarg("image", data));
    auto layout = mb.layout(figure, slider);

    mb.generate_html(layout, "sandpile.html");
}
