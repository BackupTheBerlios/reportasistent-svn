<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

  <msxsl:script language="JScript" implements-prefix="dedek">

	function RGB(val, max)
	{
		return "#ff"
			 	+ hex2(val/max)
				+ hex2(val/max);
	}

	function hex2(cislo)
	{
		var ret = (255 - Math.round(cislo * 255)).toString(16);

		if (ret.length == 1)
			return "0" + ret;
		else
			return ret;
	}



	function hex(cislo)
	{
		return cislo.toString(16);
	}

  </msxsl:script>



<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="SumShow">true</xsl:variable>
<xsl:variable name="ColourHighlighting">true</xsl:variable>
<xsl:variable name="TypeOfValues">Absolute</xsl:variable>
<xsl:variable name="BorderGrey">true</xsl:variable>

      

	<xsl:template match="hyp_4ft">

		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderGrey='true'">#eeeeee</xsl:when>
				<xsl:otherwise>#ffffff</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="id_base" select="@id" />
		<xsl:variable name="sum_1row" select="@a + @b" />
		<xsl:variable name="sum_2row" select="@c + @d" />
		<xsl:variable name="sum_1col" select="@a + @c" />
		<xsl:variable name="sum_2col" select="@b + @d" />
		<xsl:variable name="sum_total" select="@a + @b + @c + @d" />
		<xsl:variable name="rozmer_tabulky"><xsl:if test="$SumShow='false'">3</xsl:if><xsl:if test="$SumShow='true'">4</xsl:if></xsl:variable>
		
		
		<xsl:variable name="a">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@a" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@a div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		
		<xsl:variable name="b">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@b" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@b div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="c">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@c" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@c div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="d">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@d" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@d div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="r1">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_1row" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round(($sum_1row div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="r2">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_2row" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round(($sum_2row div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="c1">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_1col" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round(($sum_1col div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="c2">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_2col" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round(($sum_2col div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="total">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_total" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round(($sum_total div $sum_total) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		



		<paragraph>
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$rozmer_tabulky" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$rozmer_tabulky" /></xsl:attribute>
				<tr id="{$id_base}r1">
					<td id="{$id_base}r1d1" bgcolor="{$border_color}">
						<xsl:if test="$TypeOfValues='Relative'">
							<text id="{$id_base}r1d1text">(%)</text> 
						</xsl:if>
					</td>
					
					<td id="{$id_base}r1d2" bgcolor="{$border_color}">
						<text id="{$id_base}r1d2text">succedent</text> 
					</td>
					
					<td id="{$id_base}r1d3" bgcolor="{$border_color}">
						<text id="{$id_base}r1d3text">¬ succedent</text> 
					</td>
					<xsl:if test="$SumShow='true'">
						<td id="{$id_base}r1d4" bgcolor="{$border_color}">
							<text id="{$id_base}r1d4text">sum of values</text> 
						</td>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r2">
					<td id="{$id_base}r2d1" bgcolor="{$border_color}">
						<text id="{$id_base}r2d1text">antecedent</text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d2</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($a) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d2text"><xsl:value-of select="$a" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d3</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($b) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d3text"><xsl:value-of select="$b" /></text> 
					</xsl:element>
						
					
					<xsl:if test="$SumShow='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d4</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($r1) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d4text"><xsl:value-of select="$r1" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r3">
					
					<td id="{$id_base}r3d1" bgcolor="{$border_color}">
						<text id="{$id_base}r3d1text">¬ antecedent</text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d2</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$c" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d3</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($d) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d3text"><xsl:value-of select="$d" /></text> 
					</xsl:element>
						
					
					<xsl:if test="$SumShow='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d4</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($r2) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d4text"><xsl:value-of select="$r2" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				<xsl:if test="$SumShow='true'">
					<tr id="{$id_base}r4">
						<td id="{$id_base}r4d1" bgcolor="{$border_color}">
							<text id="{$id_base}r4d1text">sum of values</text> 
						</td>
						
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r4d2</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c1) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r4d2text"><xsl:value-of select="$c1" /></text> 
						</xsl:element>
						
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r4d3</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c2) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$c2" /></text> 
						</xsl:element>
						
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r4d4</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
							<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(0 , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r4d4text"><xsl:value-of select="$total" /></text> 
					</xsl:element>
						
					</tr>
				</xsl:if>
							
			</xsl:element>
		</paragraph>



	</xsl:template>
	




</xsl:stylesheet>
