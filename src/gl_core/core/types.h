#ifndef CORE_TYPES_H_
#define CORE_TYPES_H_

struct position { // relativistic 4 position
    float ct, x, y, z;
};

struct velocity {
    float dct, dx, dy, dz;
};

struct acceleration {
    float ddct, ddx, ddy, ddz;
};

struct energy {
    float total, potential, kinetic;
};

struct mass {
    float m;
};

struct tensor {

};

#endif // CORE_TYPES_H_

// Quantity	SI unit	Dimension
// symbol
// Name(s)                  	(Common) symbol(s)	Name	Symbol
// Length                   	l, x, r	metre	m	L
// Time                     	t	second	s	T
// Mass                     	m	kilogram	kg	M
// Thermodynamic temperature	T	kelvin	K	Θ
// Amount of substance      	n	mole	mol	N
// Electric current         	i, I	ampere	A	I
// Luminous intensity       	Iv	candela	cd	J