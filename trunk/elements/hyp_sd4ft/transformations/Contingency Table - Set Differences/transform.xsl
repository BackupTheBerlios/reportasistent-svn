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
<xsl:variable name="SumShow">false</xsl:variable>
<xsl:variable name="ColourHighlighting">false</xsl:variable>
<xsl:variable name="TypeOfValues">Absolute</xsl:variable>
<xsl:variable name="BorderGrey">true</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
      


<!-- nastaveni jazyka (defaultne cestina)-->
<xsl:variable name="lng">cz</xsl:variable>



<!-- nastaveni jazykovych popisku (labelu) -->


<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>	
		<xsl:when test="$lng='cz'">součet</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_tab_header">   <!-- hlavicka tabulky-->
	<xsl:choose>	
		<xsl:when test="$lng='cz'">Rozdíly množin</xsl:when>
		<xsl:when test="$lng='en'">Set differences</xsl:when>
		<xsl:otherwise>Set differences</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_item1">   <!-- 1. polozka tabulky-->
	<xsl:choose>	
		<xsl:when test="$lng='cz'">První množina</xsl:when>
		<xsl:when test="$lng='en'">First set</xsl:when>
		<xsl:otherwise>First set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_item2">   <!-- 2. polozka tabulky-->
	<xsl:choose>	
		<xsl:when test="$lng='cz'">Druhá množina</xsl:when>
		<xsl:when test="$lng='en'">Second set</xsl:when>
		<xsl:otherwise>Second set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_set_number">   <!-- nadpis tabulky: cislo mnoziny-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Rozdíly množin</xsl:when>
		<xsl:when test="$lng='en'">Set differences</xsl:when>
		<xsl:otherwise>Set differences</xsl:otherwise>
	</xsl:choose>
</xsl:variable>



<!-- TEMPLATES -->


	<xsl:template match="hyp_sd4ft">
		
		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderGrey='true'">#eeeeee</xsl:when>
				<xsl:otherwise>#ffffff</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		
		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="sum_total_set1" select="@a + @b + @c + @d" />
		<xsl:variable name="sum_total_set2" select="@e + @f + @g + @h" />
		
		<xsl:variable name="pocet_radku">3</xsl:variable>
		<xsl:variable name="pocet_sloupcu"><xsl:if test="$SumShow='false'">5</xsl:if><xsl:if test="$SumShow='true'">6</xsl:if></xsl:variable>
		
		
		<xsl:variable name="a">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@a" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@a div $sum_total_set1) * 100)" />
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
					<xsl:value-of select="round((@b div $sum_total_set1) * 100)" />
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
					<xsl:value-of select="round((@c div $sum_total_set1) * 100)" />
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
					<xsl:value-of select="round((@d div $sum_total_set1) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		
		<xsl:variable name="e">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@e" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@e div $sum_total_set2) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		
		<xsl:variable name="f">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@f" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@f div $sum_total_set2) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="g">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@g" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@g div $sum_total_set2) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="h">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="@h" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">
					<xsl:value-of select="round((@h div $sum_total_set2) * 100)" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		
		
		<xsl:variable name="total_set1">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_total_set1" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">100</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		
		<xsl:variable name="total_set2">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Absolute'">
					<xsl:value-of select="$sum_total_set2" />
				</xsl:when>
			</xsl:choose>
			<xsl:choose>
				<xsl:when test="$TypeOfValues='Relative'">100</xsl:when>
			</xsl:choose>
		</xsl:variable>



		<paragraph>
			
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$pocet_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$pocet_radku" /></xsl:attribute>
				<tr id="{$id_base}r1">
					<td id="{$id_base}r1d1" bgcolor="{$border_color}">
						<xsl:if test="$TypeOfValues='Relative'">
							<text id="{$id_base}r1d1text">(%)</text> 
						</xsl:if>
					</td>
					
					<td id="{$id_base}r1d2" bgcolor="{$border_color}">
						<text id="{$id_base}r1d2text">ant &amp; suc</text> 
					</td>
					
					<td id="{$id_base}r1d3" bgcolor="{$border_color}">
						<text id="{$id_base}r1d3text">ant &amp; ¬suc</text> 
					</td>
					
					<td id="{$id_base}r1d4" bgcolor="{$border_color}">
						<text id="{$id_base}r1d4text">¬ant &amp; suc</text> 
					</td>
					
					<td id="{$id_base}r1d5" bgcolor="{$border_color}">
						<text id="{$id_base}r1d5text">¬ant &amp; ¬suc</text> 
					</td>
					<xsl:if test="$SumShow='true'">
						<td id="{$id_base}r1d6" bgcolor="{$border_color}">
							<text id="{$id_base}r1d6text"><xsl:value-of select="$label_sum"/></text> 
						</td>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r2">
					<td id="{$id_base}r2d1" bgcolor="{$border_color}">
						<text id="{$id_base}r2d1text"><xsl:value-of select="$label_item1"/></text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d2</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($a) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d2text"><xsl:value-of select="$a" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d3</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($b) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d3text"><xsl:value-of select="$b" /></text> 
					</xsl:element>
						
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d4</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d4text"><xsl:value-of select="$c" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d5</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($d) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r2d5text"><xsl:value-of select="$d" /></text> 
					</xsl:element>
					
					
					
					<xsl:if test="$SumShow='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d6</xsl:attribute>
							<text id="{$id_base}r2d6text"><xsl:value-of select="$total_set1" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				
				<tr id="{$id_base}r3">
					
					<td id="{$id_base}r3d1" bgcolor="{$border_color}">
						<text id="{$id_base}r3d1text"><xsl:value-of select="$label_item2"/></text> 
					</td>
					
					
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d2</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($e) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$e" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d3</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($f) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d3text"><xsl:value-of select="$f" /></text> 
					</xsl:element>
						
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d4</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($g) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d4text"><xsl:value-of select="$g" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d5</xsl:attribute>
							<xsl:if test="$ColourHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($h) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<text id="{$id_base}r3d5text"><xsl:value-of select="$h" /></text> 
					</xsl:element>
					
					
					
					<xsl:if test="$SumShow='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d6</xsl:attribute>
							<text id="{$id_base}r3d6text"><xsl:value-of select="$total_set2" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				
							
			</xsl:element>
			
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}title"><br/><xsl:text>Tab: </xsl:text><xsl:value-of select="$label_set_number"/><br/></text> 
			</xsl:if>			
			
		</paragraph>



	</xsl:template>
	




</xsl:stylesheet>
