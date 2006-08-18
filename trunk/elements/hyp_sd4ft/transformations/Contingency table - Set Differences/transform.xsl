<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">



<!-- nastaveni jazyka (defaultne cestina)-->
<xsl:variable name="lng">cz</xsl:variable>



  <msxsl:script language="JScript" implements-prefix="dedek">


	
	function max4(a, b, c, d)
	{
		return Math.max(a,b,c,d);
	}
	
	
	
	function max2(x, y)
	{
		return Math.max(x,y);
	}
	
	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}

	
	function difference(x, y, delitel1, delitel2)
	{
	    var d1 = delitel1;
		if (d1 == 0)
			d1 = 1;
		var d2 = delitel2;
		if (d2 == 0)
			d2 = 1;
		return (Math.abs((x/d1) - (y/d2)));
	}
	
	function hodnota(val, nf)
	{
		var delitel = nf;
		if (delitel == 0)
			delitel = 1;
		return (Math.round(100 * (val / delitel)));
	}
	

  </msxsl:script>



<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="TabLegend">Tab:</xsl:variable>
<xsl:variable name="TypeOfValues">rel_row</xsl:variable>
<xsl:variable name="DifType">dif_rel</xsl:variable>
<xsl:variable name="BorderHighlight">true</xsl:variable>
<xsl:variable name="BorderColor"></xsl:variable>
<xsl:variable name="BorderOutWidth">225e-2</xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
<xsl:variable name="BorderInWidth">0</xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
<xsl:variable name="BorderFrmWidth">1</xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
<xsl:variable name="AntecedentLabel">antecedent</xsl:variable>
<xsl:variable name="SuccedentLabel">succedent</xsl:variable>





<!-- nastaveni jazykovych popisku (labelu) -->
<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>
	
		<xsl:when test="$lng='cz'">součet</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
		
	</xsl:choose>
</xsl:variable>



<!-- TEMPLATES-->      


	<xsl:template match="hyp_sd4ft">
	

		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderHighlight='true'"><xsl:value-of select="$BorderColor" /></xsl:when>
				<xsl:otherwise></xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="id_base" select="@id" />
		
	
		
		<xsl:variable name="rozmer_tabulky">3</xsl:variable>
		
		
		<!-- nastaveni tloustky ohraniceni-->
		
	<xsl:variable name="bord_out"><xsl:value-of select="$BorderOutWidth"/></xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
	<xsl:variable name="bord_in"><xsl:value-of select="$BorderInWidth"/></xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
	<xsl:variable name="bord_frm"><xsl:value-of select="$BorderFrmWidth"/></xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
		
		
		<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum_set1" select="@a + @b + @c + @d"/>
	<xsl:variable name="sum_r1_set1" select="@a + @b" />
	<xsl:variable name="sum_r2_set1" select="@c + @d" />
	<xsl:variable name="sum_c1_set1" select="@a + @c" />
	<xsl:variable name="sum_c2_set1" select="@b + @d" />
	
	<xsl:variable name="max_set1" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>
	<xsl:variable name="max_r1_set1" select="dedek:max2(number(@a), number(@b))"/>
	<xsl:variable name="max_r2_set1" select="dedek:max2(number(@c), number(@d))"/>
	<xsl:variable name="max_c1_set1" select="dedek:max2(number(@a), number(@c))"/>
	<xsl:variable name="max_c2_set1" select="dedek:max2(number(@b), number(@d))"/>
	
	<xsl:variable name="sum_set2" select="@e + @f + @g + @h"/>
	<xsl:variable name="sum_r1_set2" select="@e + @f" />
	<xsl:variable name="sum_r2_set2" select="@g + @h" />
	<xsl:variable name="sum_c1_set2" select="@e + @g" />
	<xsl:variable name="sum_c2_set2" select="@f + @h" />
	
	<xsl:variable name="max_set2" select="dedek:max4(number(@e), number(@f), number(@g), number(@h))"/>
	<xsl:variable name="max_r1_set2" select="dedek:max2(number(@e), number(@f))"/>
	<xsl:variable name="max_r2_set2" select="dedek:max2(number(@g), number(@h))"/>
	<xsl:variable name="max_c1_set2" select="dedek:max2(number(@e), number(@g))"/>
	<xsl:variable name="max_c2_set2" select="dedek:max2(number(@f), number(@h))"/>
	
	<!--spocitani hodnot tabulky-->
	
	<xsl:variable name="delitel1">
		<xsl:choose>
			<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="$sum_set1" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="delitel2">
		<xsl:choose>
			<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="$sum_set2" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

	<xsl:variable name="A"><xsl:value-of select="dedek:difference(number(@a), number(@e), number($delitel1), number($delitel2))" /></xsl:variable>
	<xsl:variable name="B"><xsl:value-of select="dedek:difference(number(@b), number(@f), number($delitel1), number($delitel2))" /></xsl:variable>
	<xsl:variable name="C"><xsl:value-of select="dedek:difference(number(@c), number(@g), number($delitel1), number($delitel2))" /></xsl:variable>
	<xsl:variable name="D"><xsl:value-of select="dedek:difference(number(@d), number(@h), number($delitel1), number($delitel2))" /></xsl:variable>
	
	<xsl:variable name="r1"><xsl:value-of select="number($A) + number($B)" /></xsl:variable>
	<xsl:variable name="r2"><xsl:value-of select="number($C) + number($D)" /></xsl:variable>
	<xsl:variable name="c1"><xsl:value-of select="number($A) + number($C)" /></xsl:variable>
	<xsl:variable name="c2"><xsl:value-of select="number($B) + number($D)" /></xsl:variable>
	<xsl:variable name="sum"><xsl:value-of select="number($A) + number($B) + number($C) + number($D)" /></xsl:variable>
	<xsl:variable name="max"><xsl:value-of select="dedek:max4(number($A),number($B),number($C),number($D))" /></xsl:variable>
	
	
	<xsl:variable name="value_A">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:hodnota(number($A), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:hodnota(number($A), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:hodnota(number($A), number($c1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:hodnota(number($A), number($r1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($A), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="value_B">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:hodnota(number($B), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:hodnota(number($B), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:hodnota(number($B), number($c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:hodnota(number($B), number($r1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($B), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="value_C">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:hodnota(number($C), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:hodnota(number($C), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:hodnota(number($C), number($c1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:hodnota(number($C), number($r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($C), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="value_D">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:hodnota(number($D), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:hodnota(number($D), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:hodnota(number($D), number($c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:hodnota(number($D), number($r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="dedek:hodnota(number($D), number(1))" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	


		<paragraph>
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$rozmer_tabulky" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$rozmer_tabulky" /></xsl:attribute>
				<tr id="{$id_base}r1">
					<td id="{$id_base}r1d1" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_frm}">
						<xsl:if test="$TypeOfValues!='abs'">
							<text id="{$id_base}r1d1text">(%)</text> 
						</xsl:if>
					</td>
					
					<td id="{$id_base}r1d2" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_in}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d2text"><xsl:value-of select="$SuccedentLabel"/></text> 
					</td>
					
					<td id="{$id_base}r1d3" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_out}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d3text">¬ <xsl:value-of select="$SuccedentLabel"/></text> 
					</td>
				</tr>
				
				<tr id="{$id_base}r2">
					<td id="{$id_base}r2d1" bgcolor="{$border_color}"  border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_in}">
						<text id="{$id_base}r2d1text"><xsl:value-of select="$AntecedentLabel"/></text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d2</xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d2text"><xsl:value-of select="$value_A" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d3</xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d3text"><xsl:value-of select="$value_B" /></text> 
					</xsl:element>
						
				</tr>
				
				<tr id="{$id_base}r3">
					
					<td id="{$id_base}r3d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_out}">
						<text id="{$id_base}r3d1text">¬ <xsl:value-of select="$AntecedentLabel"/></text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d2</xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$value_C" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d3</xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d3text"><xsl:value-of select="$value_D" /></text> 
					</xsl:element>
						
				</tr>
				
				
							
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}title"><br/><xsl:value-of select="$TabLegend" /><tab/><br/></text> 
			</xsl:if>

			
			
		</paragraph>



	</xsl:template>
	




</xsl:stylesheet>
