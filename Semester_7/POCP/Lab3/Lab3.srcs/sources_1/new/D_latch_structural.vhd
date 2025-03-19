library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity D_latch_structural is
	port (
		d : in std_logic;
		q, nq : out std_logic
	);
end D_latch_structural;

architecture Structural of D_latch_structural is 
attribute dont_touch : string;
attribute dont_touch of Structural : architecture is "true";
component nor2 
    port (
        in1, in2: in std_logic;
        out1 : out std_logic);
end component;
component not1
    port (
        in1: in std_logic;
        out1: out std_logic);
end component;
signal t1, t2, t3 : std_logic;
begin
	U1: not1 port map (in1 => d, out1 => t3);
	U2: nor2 port map (in1 => d, in2 => t2, out1 => t1);
	U3: nor2 port map (in1 => t3, in2 => t1, out1 => t2);
	q <= t2;
	nq <= t1;
end Structural;