----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 15.09.2024 20:44:13
-- Design Name: 
-- Module Name: group_mux - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity group_mux is
    Port ( IN_11 : in STD_LOGIC;
           IN_12 : in STD_LOGIC;
           IN_21 : in STD_LOGIC;
           IN_22 : in STD_LOGIC;
           S : in STD_LOGIC;
           Q1 : out STD_LOGIC;
           Q2 : out STD_LOGIC);
end group_mux;

architecture Behavioral of group_mux is

begin
     Q1<=IN_11 when S='0' else IN_21;    
     Q2<=IN_12 when S='0' else IN_22;
end Behavioral;
