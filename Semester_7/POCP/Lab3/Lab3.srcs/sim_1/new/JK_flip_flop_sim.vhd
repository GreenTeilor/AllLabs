library ieee;
use ieee.std_logic_1164.all;

entity JK_flip_flop_sim is
end JK_flip_flop_sim;

architecture Behavioral of JK_flip_flop_sim is
component JK_flip_flop
port(
    j, k, clk : in STD_LOGIC;
    q : out STD_LOGIC );
end component;
signal j : STD_LOGIC := '0';
signal k : STD_LOGIC := '0';
signal clk : STD_LOGIC := '0';
signal q : STD_LOGIC;
constant clock_period : time := 10 ns;
begin
	U1 : JK_flip_flop
		port map (
			j => j,
			k => k,
			clk => clk,
			q => q
		);
	clk <= not clk after clock_period;
	j <= not j after clock_period * 8;
	k <= not k after clock_period * 16;
end Behavioral;