module TOP(I0, I1, I2, I3, I4, O0, O1);
input  I0, I1, I2, I3, I4;
output O0, O1;

xor xor1(O0, I0, I1, I2, I3);
xnor xnor1(O1, I0, I1, I2, I3);

endmodule
