
#include "lemin.h"

//weight is kinda saturation but for mixing the color with background color

void aaellipse(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx, Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int i;
	int dxt, t, s, d;
	Sint16 xp, yp, xs, ys, dyt, overdraw;
	float cp;
	Uint8 weight, iweight;

	if (rx < 0 || ry < 0)
		return ;
	if (rx == 0 || ry == 0)
	{
		if (rx == 0 && ry == 0)
			;//TODO draw point(x, y, rgb, opacity, weight = 1)
		else if (rx == 0)
			;//TODO draw line(x, y - ry, x, y + ry, rgb, opacity, weight = 1)
		else
			;//TODO draw line(x - rx, y, x + rx, y, rgb, opacity, weight = 1)
		return ;
	}
	SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	/* "End points" */
	//TODO draw point(x, y + ry, rgb, opacity, weight = 1)
	//TODO draw point(x - rx, y, rgb, opacity, weight = 1)
	//TODO draw point(x, y - ry, rgb, opacity, weight = 1)
	//TODO draw point(x + rx, y + ry, rgb, opacity, weight = 1)

	overdraw = (Sint16)lrint(sqrt((D)(rx * rx + ry * ry)) * 0.01) + 1;
	dxt = (Sint16)lrint((D)(rx * rx) / sqrt((D)(rx * rx + ry * ry))) + overdraw;
	dyt = (Sint16)lrint((D)(ry * ry) / sqrt((D)(rx * rx + ry * ry))) + overdraw;

	t = 0;
	s = -2 * rx * rx * ry;
	d = 0;

	xp = x;
	yp = y - ry;

	for (i = 1; i <= dxt; i++) {
		xp--;
		d += t - (ry * ry);
		if (d >= 0)
			ys = yp - 1;
		else if ((d - s - (rx * rx)) > 0)
		{
			if ((2 * d - s - (rx * rx)) >= 0)
				ys = yp + 1;
			else
			{
				ys = yp;
				yp++;
				d -= s + (rx * rx);
				s += 2 * rx * rx;
			}
		}
		else
		{
			yp++;
			ys = yp + 1;
			d -= s + (rx * rx);
			s += 2 * rx * rx;
		}
		t -= 2 * ry * ry;

		/* Calculate alpha */
		if (s != 0)
			cp = (float) abs(d) / (float) abs(s);
		if (s == 0 || cp > 1.0)
			cp = 1.0;

		/* Calculate weights */
		weight = (Uint8) (cp * 255);
		iweight = 255 - weight;

		/* Upper half *///TODO check with (x/y + rx/ry) instead of "+ 2"
		pixelRGBAWeight(renderer, xp, yp, r, g, b, a, iweight);
		pixelRGBAWeight(renderer, (2 * x) - xp, yp, r, g, b, a, iweight);

		pixelRGBAWeight(renderer, xp, ys, r, g, b, a, weight);
		pixelRGBAWeight(renderer, (2 * x) - xp, ys, r, g, b, a, weight);

		/* Lower half */
		pixelRGBAWeight(renderer, xp, (2 * y) - yp, r, g, b, a, iweight);
		pixelRGBAWeight(renderer, (2 * x) - xp, (2 * y) - yp, r, g, b, a, iweight);

		pixelRGBAWeight(renderer, xp, (2 * y) - ys, r, g, b, a, weight);
		pixelRGBAWeight(renderer, (2 * x) - xp, (2 * y) - ys, r, g, b, a, weight);
	}

	for (i = 1; i <= dyt; i++) {
		yp++;
		d -= s + (rx * rx);

		if (d <= 0)
			xs = xp + 1;
		else if ((d + t - (ry * ry)) < 0) {
			if ((2 * d + t - (ry * ry)) <= 0)
				xs = xp - 1;
			else {
				xs = xp;
				xp--;
				d += t - (ry * ry);
				t -= (2 * ry * ry);
			}
		} else {
			xp--;
			xs = xp - 1;
			d += t - (ry * ry);
			t -= (2 * ry * ry);
		}

		s += (2 * rx * rx);

		/* Calculate alpha */
		if (t != 0) {
			cp = (float) abs(d) / (float) abs(t);
			if (cp > 1.0) {
				cp = 1.0;
			}
		} else {
			cp = 1.0;
		}

		/* Calculate weight */
		weight = (Uint8) (cp * 255);
		iweight = 255 - weight;

		/* Left half */
		pixelRGBAWeight(renderer, xp, yp, r, g, b, a, iweight);
		pixelRGBAWeight(renderer, (2 * x) - xp, yp, r, g, b, a, iweight);

		pixelRGBAWeight(renderer, xp, (2 * y) - yp, r, g, b, a, iweight);
		pixelRGBAWeight(renderer, (2 * x) - xp, (2 * y) - yp, r, g, b, a, iweight);

		/* Right half */
		pixelRGBAWeight(renderer, xs, yp, r, g, b, a, weight);
		pixelRGBAWeight(renderer, (2 * x) - xs, yp, r, g, b, a, weight);

		pixelRGBAWeight(renderer, xs, (2 * y) - yp, r, g, b, a, weight);
		pixelRGBAWeight(renderer, (2 * x) - xs, (2 * y) - yp, r, g, b, a, weight);
	}
}
