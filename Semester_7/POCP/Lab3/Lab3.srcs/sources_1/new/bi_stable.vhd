library IEEE, lcdf_vhdl;
use IEEE.STD_LOGIC_1164.ALL, lcdf_vhdl.func_prims.all;

entity bi_stable is
    Port (
        q : out STD_LOGIC;
        nq: out STD_LOGIC
    );
end bi_stable;

architecture Structural of bi_stable is
attribute dont_touch : string;
attribute dont_touch of Structural : architecture is "true";
component not1
    Port (
        in1: in STD_LOGIC;
        out1: out STD_LOGIC
    );
end component;
signal inv_0_o: STD_LOGIC;
signal inv_1_0: STD_LOGIC := '0';
begin
    inv_0: not1 port map (in1 => inv_1_0, out1 => inv_0_o);
    inv_1: not1 port map (in1 => inv_0_o, out1 => inv_1_0);
    
    q <= inv_1_0;
    nq <= inv_0_o;
end Structural;