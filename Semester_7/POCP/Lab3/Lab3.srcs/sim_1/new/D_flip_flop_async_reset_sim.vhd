library ieee;
use ieee.std_logic_1164.all;

entity D_flip_flop_async_reset_sim is
end D_flip_flop_async_reset_sim;

architecture Behavioral of D_flip_flop_async_reset_sim is
	component D_flip_flop_async_reset
	port(
		d, clk, rst : in std_logic;
		q : out std_logic );
	end component;


	signal d : std_logic := '0';
	signal clk : std_logic := '0';
	signal rst : std_logic := '0';

	signal q : std_logic;
	
	constant clock : time := 10 ns;
	constant d_period : time := clock * 4;
begin
	U1 : D_flip_flop_async_reset port map (d => d, clk => clk, rst => rst, q => q);	  
	
	d <= not d after d_period;
	clk <= not clk after clock;
	rst <= not rst after clock / 2;
end Behavioral;