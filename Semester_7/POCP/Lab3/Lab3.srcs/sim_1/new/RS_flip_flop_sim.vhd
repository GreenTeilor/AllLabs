library ieee;
use ieee.std_logic_1164.all;

entity RS_flip_flop_sim is
end RS_flip_flop_sim;

architecture Behavioral of RS_flip_flop_sim is
	component RS_flip_flop
		port(
			r, s, clk : in STD_LOGIC;
			q : out STD_LOGIC );
	end component;
	
	signal r : STD_LOGIC := '0';
	signal s : STD_LOGIC := '0';
	signal clk : STD_LOGIC := '0';
	
	signal q : STD_LOGIC;	   
	
	constant clock_period : time := 10 ns;
begin
	UUT : RS_flip_flop
	port map (
		r => r,
		s => s,
		clk => clk,
		q => q
		);
	
	clk <= not clk after clock_period;
	s <= not s after clock_period * 4;
	r <= not r after clock_period * 8;	
end Behavioral;