`include "and_using_nor_gate.v"

module and_using_nor_gate_tb;

    reg a, b;
    wire y;

and_using_nor_gate test (a, b, y);

initial begin

$monitor("Time=%0t | a=%b b=%b | y=%b", $time, a, b, y);

        a=0; b=0; #10;
        a=0; b=1; #10;
        a=1; b=0; #10;
        a=1; b=1; #10;

$finish;
end

initial begin

        $dumpfile("and_using_nor_gate.vcd");
$dumpvars();

end
endmodule