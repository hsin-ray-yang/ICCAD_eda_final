module TOP(I0, I1, I2, O0);
	input  I0, I1, I2;
	output O0;
	wire   w1;

	gate g0(I0, I1, w1);
	gate g1(w1, I2, O0);

endmodule
