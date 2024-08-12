#pragma once
#include <cstdint>

namespace MathClasses
{
	class Colour
	{
	public:

        Colour() : colour{ 0x000000ff } {}

        Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        {
            colour = colour & 0x000000ff
                | ((unsigned int)r << RED)
                | ((unsigned int)b << BLUE)
                | ((unsigned int)g << GREEN)
                | ((unsigned int)a << ALPHA);
        }

        bool IsEqual(const Colour& rhs) const {


            return (colour == rhs.colour);

        }

        bool operator==(const Colour& rhs) const
        {
            return IsEqual(rhs);
        }

        bool operator!=(const Colour& rhs) const
        {
            return !(*this == rhs);
        }

        unsigned char GetRed() const
        {
            return colour >> 24;
        }

        unsigned char GetGreen() const
        {
            return colour >> 16;
        }

        unsigned char GetBlue() const
        {
            return colour >> 8;
        }

        unsigned char GetAlpha() const
        {
            return colour;
        }

        void SetRed(unsigned char red)
        {
            unsigned int v = (unsigned int)red << RED;
            colour = colour & 0x00ffffff | v;
        }

        void SetGreen(unsigned char green)
        {
            unsigned int v = (unsigned int)green << GREEN;
            colour = colour & 0xff00ffff | v;
        }

        void SetBlue(unsigned char blue)
        {
            unsigned int v = (unsigned int)blue << BLUE;
            colour = colour & 0xffff00ff | v;

        }

        void SetAlpha(unsigned char alpha)
        {
            unsigned int v = (unsigned int)alpha;
            colour = colour & 0xffffff00 | v;
        }

	public:

		std::uint32_t colour = 0;

		enum RGBA {
			RED = 24,
			GREEN = 16,
			BLUE = 8,
			ALPHA = 0
		};

	};
}