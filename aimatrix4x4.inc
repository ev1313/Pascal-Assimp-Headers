//from matrix4x4.h
type
  TaiMatrix4x4 = packed record
	a1, a2, a3, a4: Single;
	b1, b2, b3, b4: Single;
	c1, c2, c3, c4: Single;
	d1, d2, d3, d4: Single;
  end;
  PaiMatrix4x4 = ^TaiMatrix4x4;