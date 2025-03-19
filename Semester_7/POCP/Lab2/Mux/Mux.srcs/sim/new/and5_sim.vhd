library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity and5_sim is
end and5_sim;

architecture behavioral of and5_sim is
component and5_b is
    Port (
        a : in STD_LOGIC_VECTOR(4 downto 0);
        z : out STD_LOGIC
    );
end component;
component and5_s is
    Port (
        a : in STD_LOGIC_VECTOR(4 downto 0);
        z : out STD_LOGIC
    );
end component;
signal a, b, c, d, e: STD_LOGIC;
signal z_b, z_s: STD_LOGIC;
signal error: STD_LOGIC;
signal test_vector: std_logic_vector(4 downto 0);
constant period : time := 10ns; 

begin
  UB: and5_b port map (
        a(0) => a,
        a(1) => b,
        a(2) => c,
        a(3) => d,
        a(4) => e,
        z => z_b
    );  

  US: and5_s port map (
       a(0) => a,
       a(1) => b,
       a(2) => c,
       a(3) => d,
       a(4) => e,
       z => z_s
   );
   
   a <= test_vector(0);
   b <= test_vector(1);
   c <= test_vector(2);
   d <= test_vector(3);
   e <= test_vector(4);
   
    sim_proc: process
      begin
        for i in 0 to 31 loop
          test_vector <= std_logic_vector(to_unsigned(i, test_vector'length));
              wait for period;
        end loop;  
      report "End of simulation" severity failure;  
      end process;
      error <= z_b xor z_s;

end behavioral;
