library IEEE, lcdf_vhdl;
use IEEE.STD_LOGIC_1164.ALL, lcdf_vhdl.func_prims.all;

entity D_latch_enable_structural is
    Port ( e, d : in STD_LOGIC;
           q, nq : out STD_LOGIC);
end D_latch_enable_structural;

architecture Structural of D_latch_enable_structural is
attribute dont_touch : string;
attribute dont_touch of Structural : architecture is "true";
component not1
    Port (
        in1: in STD_LOGIC;
        out1: out STD_LOGIC
    );
end component;
component and2
    Port (
        in1, in2: in STD_LOGIC;
        out1: out STD_LOGIC
    );   
end component;
component RS_latch_structural
Port (
        s, r: in STD_LOGIC;
        q, nq: out STD_LOGIC
    ); 
end component;
signal nd, ed, e_nd: STD_LOGIC;
begin
    U1_ND: not1 port map (in1 => d, out1 => nd);
    U2_ED: and2 port map (in1 => d, in2 => e, out1 => ed);
    U3_END: and2 port map (in1 => nd, in2 => e, out1 => e_nd);
    U4_RS_LATCH: RS_latch_structural port map (s => ed, r => e_nd, q => q, nq => nq);
end Structural;
