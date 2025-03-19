library ieee;
use ieee.std_logic_1164.all;

entity D_latch_enable_sim is
end D_latch_enable_sim;

architecture behavior of D_latch_enable_sim is
	component D_latch_enable_structural
	port(
		d : in std_logic;
		e : in std_logic;
		q : out std_logic;
		nq : out std_logic );
	end component;

	component D_latch_enable_behavioral
	port(
		d : in std_logic;
		e : in std_logic;
		q : out std_logic;
		nq : out std_logic );
	end component;

	component D_latch_enable_param
	port(
		d : in std_logic;
		e : in std_logic;
		q : out std_logic;
		nq : out std_logic );
	end component;

	signal d : std_logic := '0';
	signal e : std_logic := '0';

	signal q_struct : std_logic;
	signal nq_struct : std_logic;	 
	
	signal q_beh : std_logic;
	signal nq_beh : std_logic;
	
	signal q_param : std_logic;
	signal nq_param : std_logic;   
	
	constant data_clock_period : time := 10 ns;
	constant enabled_period : time := 10 ns;
	constant disabled_period : time := enabled_period * 4;
begin
	STRUCT: D_latch_enable_structural
		port map (
			d => d,
			e => e,
			q => q_struct,
			nq => nq_struct
		);	 
		
	BEH : D_latch_enable_behavioral
	port map (
		d => d,
		e => e,
		q => q_beh,
		nq => nq_beh
	);
	
	PARAM : D_latch_enable_param
	port map (
		d => d,
		e => e,
		q => q_param,
		nq => nq_param
	);
	
	d <= not d after data_clock_period;
	e <= '1' after disabled_period when e = '0' else '0' after enabled_period;	
end behavior;