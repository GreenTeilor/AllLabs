library ieee;
use ieee.std_logic_1164.all;

entity D_latch_sim is
end D_latch_sim;

architecture Behavioral of D_latch_sim is
component D_latch_behavioral
    port(
        d : in std_logic;
        q, nq : out std_logic );
end component;

component D_latch_param
    port(
        d : in std_logic;
        q, nq : out std_logic );
end component;

component D_latch_structural
    port(
        d : in std_logic;
        q, nq : out std_logic);
end component;

signal d : std_logic := '0';

signal q_struct : std_logic;
signal nq_struct : std_logic;

signal q_beh : std_logic;
signal nq_beh : std_logic;	

signal q_param : std_logic;
signal nq_param : std_logic;
begin
STRUCT : D_latch_structural
port map (
    d => d,
    q => q_struct,
    nq => nq_struct
    ); 

BEH : D_latch_behavioral
port map (
    d => d,
    q => q_beh,
    nq => nq_beh
    );	  

PARAM : D_latch_param
port map (
    d => d,
    q => q_param,
    nq => nq_param
    ); 

d <= not d after 100 ns;
end Behavioral;