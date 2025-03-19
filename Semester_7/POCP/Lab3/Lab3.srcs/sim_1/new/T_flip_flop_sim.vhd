library ieee;
use ieee.std_logic_1164.all;

entity T_flip_flop_sim is
end T_flip_flop_sim;

architecture Behavioral of T_flip_flop_sim is
	component T_flip_flop_behavioral
	port(
		t, clk, clr : in std_logic;
		q : out std_logic
	);
	end component;

	signal t : std_logic := '0';
	signal clk : std_logic := '0';
	signal clr : std_logic := '1';
	
	signal q : std_logic;
	
	constant clock : integer := 10;
	constant clk_period : time := clock * 1 ns;
	constant clr_period : time := ((clock * 10) - (clock / 2)) * 1 ns;

begin
	U1: T_flip_flop_behavioral
		port map (t => t, q => q, clk => clk, clr => clr);
		
	clk <= not clk after clk_period;
	t <= not t after clk_period * 8;
	clr <= '1' after clr_period when clr = '0' else '0' after clk_period;
end Behavioral;