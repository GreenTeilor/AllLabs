library IEEE, lcdf_vhdl;
use IEEE.STD_LOGIC_1164.ALL, lcdf_vhdl.func_prims.all;

entity RS_latch_structural is
    Port ( S, R : in STD_LOGIC;
           Q, nQ : out STD_LOGIC);
end RS_latch_structural;

architecture Structural of RS_latch_structural is
attribute dont_touch : string;
attribute dont_touch of Structural : architecture is "true";
component nor2 is
    Port (
        in1, in2: in STD_LOGIC;
        out1: out STD_LOGIC
    );
end component;
signal q1_s, q2_s: STD_LOGIC;
begin
    nor2_0: nor2 port map (in1 => R, in2 => q1_s, out1 => q2_s);
    nor2_1: nor2 port map (in1 => q2_s, in2 => S, out1 => q1_s);
    
    Q <= q2_s;
    nQ <= q1_s;
end Structural;
