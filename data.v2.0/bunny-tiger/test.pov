// Persistence Of Vision raytracer version 3.0 sample file.
// Demonstrates ppd. 

#version 3.0
global_settings { assumed_gamma 2.2 }

#include "colors.inc"
#include "shapes.inc"
#include "textures.inc"

#declare WHITE_BUNNY = texture {
	finish { Shiny }
	pigment { White }
}

#include "test.inc"

camera {
	location <0.940367, 0.246152, 2.72297>
	right -x*1.333
	up y
	direction z
	angle 45
	look_at <0, 0, 0>
}

light_source { <20, 20, 20> color White }
light_source { <-20, 20, 20> color White }

sky_sphere { pigment { rgb <1, 0.894, 0.769> } }
