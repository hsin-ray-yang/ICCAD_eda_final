module TOP(I0, I1, I2, O0);
input  I0, I1, I2;
output O0;
wire   w1;

buf b0(w1, I0);
buf b1(O0, w1);

endmodule
