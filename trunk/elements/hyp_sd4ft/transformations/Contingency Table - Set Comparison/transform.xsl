<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">



<!-- nastaveni jazyka (defaultne cestina)-->
<xsl:variable name="lng">cz</xsl:variable>



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



  </msxsl:script>



<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="SumShow">true</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="TabLegend">Tab. </xsl:variable>
<xsl:variable name="ColorHighlighting">true</xsl:variable>
<xsl:variable name="TypeOfValues">abs</xsl:variable>
<xsl:variable name="BorderHighlight">true</xsl:variable>
<xsl:variable name="BorderColor">#eeeeee</xsl:variable>
<xsl:variable name="BorderOutWidth">225e-2</xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
<xsl:variable name="BorderInWidth">0</xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
<xsl:variable name="BorderFrmWidth">1</xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
<xsl:variable name="AntecedentLabel">antecedent</xsl:variable>
<xsl:variable name="SuccedentLabel">succedent</xsl:variable>
<xsl:variable name="NotAntecedentLabel">¬ antecedent</xsl:variable>
<xsl:variable name="NotSuccedentLabel">¬ succedent</xsl:variable>





<!-- nastaveni jazykovych popisku (labelu) -->
<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>
	
		<xsl:when test="$lng='cz'">součet</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
		
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_first_set">   <!-- nadpis tabulky: prvni mnozina-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">První množina</xsl:when>
		<xsl:when test="$lng='en'">First set</xsl:when>
		<xsl:otherwise>First set</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_second_set">   <!-- nadpis tabulky: druha mnozina-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Druhá množina</xsl:when>
		<xsl:when test="$lng='en'">Second set</xsl:when>
		<xsl:otherwise>Second set</xsl:otherwise>
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
		
		<xsl:variable name="ShowSumField">
			<xsl:choose>
				<xsl:when test="$SumShow='true' and $TypeOfValues='abs'">true</xsl:when>
				<xsl:otherwise>false</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		
		<xsl:variable name="rozmer_tabulky_radku">3</xsl:variable>
		
		<xsl:variable name="rozmer_tabulky_sloupcu">
			<xsl:choose>
				<xsl:when test="$ShowSumField='true'">6</xsl:when>
				<xsl:otherwise>5</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		
		<!-- nastaveni tloustky ohraniceni-->
		
	<xsl:variable name="bord_out"><xsl:value-of select="$BorderOutWidth"/></xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
	<xsl:variable name="bord_in"><xsl:value-of select="$BorderInWidth"/></xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
	<xsl:variable name="bord_frm"><xsl:value-of select="$BorderFrmWidth"/></xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
		
		
		<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum_set1" select="@a + @b + @c + @d"/>
	<xsl:variable name="max_set1" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>

	<xsl:variable name="sum_set2" select="@e + @f + @g + @h"/>
	<xsl:variable name="max_set2" select="dedek:max4(number(@e), number(@f), number(@g), number(@h))"/>
	
	<!--spocitani hodnot tabulky-->
	
			<!-- First set-->
			
	<xsl:variable name="a">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_set1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@a), number($max_set1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@a" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="b">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_set1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@b), number($max_set1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@b" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_set1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@c), number($max_set1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@c" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="d">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_set1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@d), number($max_set1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@d" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	
	<xsl:variable name="total_set1">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='abs'"><xsl:value-of select="$sum_set1" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

		
	
			<!-- Second set-->
	
	<xsl:variable name="e">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@e), number($sum_set2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@e), number($max_set2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@e" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="f">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@f), number($sum_set2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@f), number($max_set2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@f" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="g">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@g), number($sum_set2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@g), number($max_set2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@g" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="h">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@h), number($sum_set2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@h), number($max_set2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@h" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>


	<xsl:variable name="total_set2">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='abs'"><xsl:value-of select="$sum_set2" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	






		<paragraph>
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$rozmer_tabulky_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$rozmer_tabulky_radku" /></xsl:attribute>
				<tr id="{$id_base}r1">
					<td id="{$id_base}r1d1" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_frm}">
						<xsl:if test="$TypeOfValues!='abs'">
							<text id="{$id_base}r1d1text">(%)</text> 
						</xsl:if>
					</td>
					
					<td id="{$id_base}r1d2" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_in}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d2text"><xsl:value-of select="$AntecedentLabel"/> &amp; <xsl:value-of select="$SuccedentLabel"/></text> 
					</td>
					
					<td id="{$id_base}r1d3" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_in}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d3text"><xsl:value-of select="$AntecedentLabel"/> &amp; <xsl:value-of select="$NotSuccedentLabel"/></text> 
					</td>
					<td id="{$id_base}r1d4" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_in}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d4text"><xsl:value-of select="$NotAntecedentLabel"/> &amp; <xsl:value-of select="$SuccedentLabel"/></text> 
					</td>
					
					<td id="{$id_base}r1d4" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_out}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d4text"><xsl:value-of select="$NotAntecedentLabel"/> &amp; <xsl:value-of select="$NotSuccedentLabel"/></text> 
					</td>
					<xsl:if test="$ShowSumField='true'">
						<td id="{$id_base}r1d6" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_frm}" border_right="{$bord_out}" border_bottom="{$bord_frm}">
							<text id="{$id_base}r1d6text"><xsl:value-of select="$label_sum"/></text> 
						</td>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r2">
					<td id="{$id_base}r2d1" bgcolor="{$border_color}"  border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_in}">
						<text id="{$id_base}r2d1text"><xsl:value-of select="$label_first_set"/></text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d2</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($a) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d2text"><xsl:value-of select="$a" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d3</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($b) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d3text"><xsl:value-of select="$b" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d4</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d4text"><xsl:value-of select="$c" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d5</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($d) , number($total_set1))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d5text"><xsl:value-of select="$d" /></text> 
					</xsl:element>
						
					
					<xsl:if test="$ShowSumField='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d6</xsl:attribute>
							<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>							
							<text id="{$id_base}r2d6text"><xsl:value-of select="$total_set1" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r3">
					
					<td id="{$id_base}r3d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_out}">
						<text id="{$id_base}r3d1text"><xsl:value-of select="$label_second_set"/></text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d2</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($e) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$e" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d3</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($f) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d3text"><xsl:value-of select="$f" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d4</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($g) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d4text"><xsl:value-of select="$g" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d5</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($h) , number($total_set2))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d5text"><xsl:value-of select="$h" /></text> 
					</xsl:element>
						
					
					<xsl:if test="$ShowSumField='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d6</xsl:attribute>
							<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_in"/></xsl:attribute>							
							<text id="{$id_base}r3d6text"><xsl:value-of select="$total_set1" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				
							
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}title"><br/><xsl:value-of select="$TabLegend" /><tab/><br/></text> 
			</xsl:if>

			
			
		</paragraph>

		
	




	</xsl:template>
	




</xsl:stylesheet>
