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
<xsl:variable name="TabLegend">Tab:</xsl:variable>
<xsl:variable name="ColorHighlighting">true</xsl:variable>
<xsl:variable name="TypeOfValues">rel_row</xsl:variable>
<xsl:variable name="BorderHighlight">true</xsl:variable>
<xsl:variable name="BorderColor"></xsl:variable>
<xsl:variable name="BorderOutWidth">225e-2</xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
<xsl:variable name="BorderInWidth">0</xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
<xsl:variable name="BorderFrmWidth">1</xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
<xsl:variable name="AntecedentLabel">antecedent</xsl:variable>
<xsl:variable name="SuccedentLabel">succedent</xsl:variable>
<xsl:variable name="NotAntecedentLabel">� antecedent</xsl:variable>
<xsl:variable name="NotSuccedentLabel">� succedent</xsl:variable>

  <!--specialni promenna - SpecialString ... pokud je hodnota AntecedentLabel ... NotSuccedentLabel nastavena na tuto
  hodnotu, nahradi se prislusnou hodnotou skutecneho cedentu-->
  <xsl:variable name="SpecialString">***</xsl:variable>


<!-- nastaveni jazykovych popisku (labelu) -->
<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>
	
		<xsl:when test="$lng='cz'">sou�et</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
		
	</xsl:choose>
</xsl:variable>



<!-- TEMPLATES-->      


	<xsl:template match="hyp_4ft">
	

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
		
		
		<xsl:variable name="rozmer_tabulky">
			<xsl:choose>
				<xsl:when test="$ShowSumField='true'">4</xsl:when>
				<xsl:otherwise>3</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

    <!--hodnoty cedentu-->
    <xsl:variable name="antecedent_str">
      <xsl:for-each select="id(@antecedent)/ti_literal">
        <xsl:if test="position()!=1">
          <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
        </xsl:if>
        <xsl:value-of select="@quant"/>
        <xsl:text disable-output-escaping="yes">(</xsl:text>
        <xsl:value-of select="@value"/>
        <xsl:text disable-output-escaping="yes">)</xsl:text>
      </xsl:for-each>
      <xsl:if test="count(id(@antecedent)/ti_literal)=0">
        <xsl:choose>
          <xsl:when test="$lng='cz'">bez omezen�</xsl:when>
          <xsl:otherwise>no restriction</xsl:otherwise>
        </xsl:choose>
      </xsl:if>
    </xsl:variable>

    <xsl:variable name="succedent_str">
      <xsl:for-each select="id(@succedent)/ti_literal">
        <xsl:if test="position()!=1">
          <xsl:text disable-output-escaping="no"> &amp; </xsl:text>
        </xsl:if>
        <xsl:value-of select="@quant"/>
        <xsl:text disable-output-escaping="yes">(</xsl:text>
        <xsl:value-of select="@value"/>
        <xsl:text disable-output-escaping="yes">)</xsl:text>
      </xsl:for-each>
      <xsl:if test="count(id(@succedent)/ti_literal)=0">
        <xsl:choose>
          <xsl:when test="$lng='cz'">bez omezen�</xsl:when>
          <xsl:otherwise>no restriction</xsl:otherwise>
        </xsl:choose>
      </xsl:if>
    </xsl:variable>
		
		
		<!-- nastaveni tloustky ohraniceni-->
		
	<xsl:variable name="bord_out"><xsl:value-of select="$BorderOutWidth"/></xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
	<xsl:variable name="bord_in"><xsl:value-of select="$BorderInWidth"/></xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
	<xsl:variable name="bord_frm"><xsl:value-of select="$BorderFrmWidth"/></xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
		
		
		<!-- hodnoty cisel, souctu a maxima-->
	
	
	<xsl:variable name="sum" select="@a + @b + @c + @d"/>
	<xsl:variable name="sum_r1" select="@a + @b" />
	<xsl:variable name="sum_r2" select="@c + @d" />
	<xsl:variable name="sum_c1" select="@a + @c" />
	<xsl:variable name="sum_c2" select="@b + @d" />
	
	<xsl:variable name="max" select="dedek:max4(number(@a), number(@b), number(@c), number(@d))"/>
	<xsl:variable name="max_r1" select="dedek:max2(number(@a), number(@b))"/>
	<xsl:variable name="max_r2" select="dedek:max2(number(@c), number(@d))"/>
	<xsl:variable name="max_c1" select="dedek:max2(number(@a), number(@c))"/>
	<xsl:variable name="max_c2" select="dedek:max2(number(@b), number(@d))"/>
	
	<!--spocitani hodnot grafu-->
	
	<xsl:variable name="a">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@a), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_c1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@a), number($sum_r1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@a" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="b">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@b), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@b), number($sum_r1))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@b" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@c), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_c1))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@c), number($sum_r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@c" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="d">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number(@d), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number(@d), number($sum_r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="@d" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="r1">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number($sum_r1), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number($sum_r1), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number($sum_r1), number($sum_c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number($sum_r1), number($sum_r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="$sum_r1" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="r2">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number($sum_r2), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number($sum_r2), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number($sum_r2), number($sum_c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number($sum_r2), number($sum_r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="$sum_r2" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c1">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number($sum_c1), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number($sum_c1), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number($sum_c1), number($sum_c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number($sum_c1), number($sum_r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="$sum_c1" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="c2">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="dedek:normalize_value(number($sum_c2), number($sum))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="dedek:normalize_value(number($sum_c2), number($max))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="dedek:normalize_value(number($sum_c2), number($sum_c2))" /></xsl:when>
			<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="dedek:normalize_value(number($sum_c2), number($sum_r2))" /></xsl:when>
			<xsl:otherwise><xsl:value-of select="$sum_c2" /></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	
	<xsl:variable name="total">
		<xsl:choose>
			<xsl:when test="$TypeOfValues='abs'"><xsl:value-of select="$sum" /></xsl:when>
			<xsl:otherwise>100</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>

    <!--Kody - pokud je hodnota $AntecedentLabel, $SuccedentLabel, $Not.... nastavena na $SpecialString, vlozi se na misto ni skutecna hodnota prislusneho cedentu-->	
    
		



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
						<text id="{$id_base}r1d2text">
              <xsl:choose>
                <xsl:when test="$SuccedentLabel=$SpecialString">
                  <xsl:value-of select="$succedent_str" />
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$SuccedentLabel"/>
                </xsl:otherwise>
              </xsl:choose>
            </text> 
					</td>
					
					<td id="{$id_base}r1d3" bgcolor="{$border_color}" border_top="{$bord_out}"  border_right="{$bord_out}" border_bottom="{$bord_frm}">
						<text id="{$id_base}r1d3text">
              <xsl:choose>
                <xsl:when test="$NotSuccedentLabel=$SpecialString">
                  <xsl:text>NOT </xsl:text>
                  <xsl:value-of select="$succedent_str" />
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$NotSuccedentLabel"/>
                </xsl:otherwise>
              </xsl:choose>
            </text> 
					</td>
					<xsl:if test="$ShowSumField='true'">
						<td id="{$id_base}r1d4" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_frm}" border_right="{$bord_out}" border_bottom="{$bord_frm}">
							<text id="{$id_base}r1d4text"><xsl:value-of select="$label_sum"/></text> 
						</td>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r2">
					<td id="{$id_base}r2d1" bgcolor="{$border_color}"  border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_in}">
            <text id="{$id_base}r2d1text">
              <xsl:choose>
                <xsl:when test="$AntecedentLabel=$SpecialString">
                  <xsl:value-of select="$antecedent_str" />
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$AntecedentLabel"/>
                </xsl:otherwise>
              </xsl:choose>
            </text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d2</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($a) , number($total))" />
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
									<xsl:value-of select="dedek:RGB(number($b) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<text id="{$id_base}r2d3text"><xsl:value-of select="$b" /></text> 
					</xsl:element>
						
					
					<xsl:if test="$ShowSumField='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r2d4</xsl:attribute>
							<!--<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($r1) , number($total))" />
								</xsl:attribute>
							</xsl:if>-->
							<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>							
							<text id="{$id_base}r2d4text"><xsl:value-of select="$r1" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				<tr id="{$id_base}r3">
					
					<td id="{$id_base}r3d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_out}">
						<text id="{$id_base}r3d1text">
              <xsl:choose>
                <xsl:when test="$NotAntecedentLabel=$SpecialString">
                  <xsl:text>NOT </xsl:text>
                  <xsl:value-of select="$antecedent_str" />
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="$NotAntecedentLabel"/>
                </xsl:otherwise>
              </xsl:choose>
            </text> 
					</td>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d2</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$c" /></text> 
					</xsl:element>
					
					<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d3</xsl:attribute>
							<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($d) , number($total))" />
								</xsl:attribute>
							</xsl:if>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<text id="{$id_base}r3d3text"><xsl:value-of select="$d" /></text> 
					</xsl:element>
						
					
					<xsl:if test="$ShowSumField='true'">
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r3d4</xsl:attribute>
							<!--<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($r2) , number($total))" />
								</xsl:attribute>
							</xsl:if>-->
							<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_in"/></xsl:attribute>							
							<text id="{$id_base}r3d4text"><xsl:value-of select="$r2" /></text> 
						</xsl:element>
					</xsl:if>
				</tr>
				
				<xsl:if test="$ShowSumField='true'">
					<tr id="{$id_base}r4">
						<td id="{$id_base}r4d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_out}" border_top="{$bord_frm}">
							<text id="{$id_base}r4d1text"><xsl:value-of select="$label_sum"/></text> 
						</td>
						
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r4d2</xsl:attribute>
							<!--<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c1) , number($total))" />
								</xsl:attribute>
							</xsl:if>-->
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<text id="{$id_base}r4d2text"><xsl:value-of select="$c1" /></text> 
						</xsl:element>
						
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r4d3</xsl:attribute>
							<!--<xsl:if test="$ColorHighlighting='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(number($c2) , number($total))" />
								</xsl:attribute>
							</xsl:if>-->
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<text id="{$id_base}r3d2text"><xsl:value-of select="$c2" /></text> 
						</xsl:element>
						
						<xsl:element name="td">
							<xsl:attribute name="id"><xsl:value-of select="$id_base"/>r4d4</xsl:attribute>
							<!--<xsl:if test="$ColorHighlighting='true'">
							  <xsl:attribute name="bgcolor">
									<xsl:value-of select="dedek:RGB(0 , number($total))" />
								</xsl:attribute>
							</xsl:if>-->
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<text id="{$id_base}r4d4text"><xsl:value-of select="$total" /></text> 
					</xsl:element>
						
					</tr>
				</xsl:if>
							
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}title"><br/><xsl:value-of select="$TabLegend" /><tab/><br/></text> 
			</xsl:if>

			
			
		</paragraph>



	</xsl:template>
	




</xsl:stylesheet>
