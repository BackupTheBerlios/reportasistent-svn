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

	
	function normalize_value(co, cim)
	{
		return Math.round(100*(co/cim));
	}


  </msxsl:script>


<!-- klic - atributy-->
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />


<!-- Promenne - nastaveni vizualizaci-->

<xsl:variable name="SumShow">true</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="TabLegend">Tab:</xsl:variable>
<xsl:variable name="ColorHighlighting">true</xsl:variable>
<xsl:variable name="TypeOfValues">abs</xsl:variable>
<xsl:variable name="BorderHighlight">true</xsl:variable>
<xsl:variable name="BorderColor">#eeeeee</xsl:variable>
<xsl:variable name="BorderOutWidth">225e-2</xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
<xsl:variable name="BorderInWidth">0</xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
<xsl:variable name="BorderFrmWidth">1</xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
<xsl:variable name="TablePosition">Horisontal</xsl:variable>
  

<!-- nastaveni jazykovych popisku (labelu) -->


<xsl:variable name="label_sum">   <!-- label v tabulce v kolonkach souctu-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">součet</xsl:when>
		<xsl:when test="$lng='en'">sum</xsl:when>
		<xsl:otherwise>sum</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


<xsl:variable name="label_cat">   <!-- nadpis tabulky: Category-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Kategorie</xsl:when>
		<xsl:when test="$lng='en'">Category</xsl:when>
		<xsl:otherwise>Category</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_freq">   <!-- nadpis tabulky: cislo mnoziny-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Frekvence</xsl:when>
		<xsl:when test="$lng='en'">Frequency</xsl:when>
		<xsl:otherwise>Frequency</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


    
    
    
    <!-- nastaveni tloustky ohraniceni-->
		
	<xsl:variable name="bord_out"><xsl:value-of select="$BorderOutWidth"/></xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
	<xsl:variable name="bord_in"><xsl:value-of select="$BorderInWidth"/></xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
	<xsl:variable name="bord_frm"><xsl:value-of select="$BorderFrmWidth"/></xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->

    
    
    
<!-- TEMPLATES -->


      



	<xsl:template match="hyp_cf">
		
		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderHighlight='true'"><xsl:value-of select="$BorderColor" /></xsl:when>
				<xsl:otherwise></xsl:otherwise>
			</xsl:choose>
		</xsl:variable>


		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="pocet_radku">
			<xsl:choose>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:text>2</xsl:text>
				</xsl:when>
				<xsl:when test="$TablePosition='Vertical'">
					<xsl:choose>
						<xsl:when test="$SumShow='true' and $TypeOfValues='abs'"><xsl:value-of select="count(r[position()=1]/c) + 2" /></xsl:when>
						<xsl:otherwise><xsl:value-of select="count(r[position()=1]/c) + 1" /></xsl:otherwise>
					</xsl:choose>
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>
		
		<xsl:variable name="pocet_sloupcu">
			<xsl:choose>
				<xsl:when test="$TablePosition='Vertical'">
					<xsl:text>2</xsl:text>
				</xsl:when>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:choose>
						<xsl:when test="$SumShow='true' and $TypeOfValues='abs'"><xsl:value-of select="count(r[position()=1]/c) + 2" /></xsl:when>
						<xsl:otherwise><xsl:value-of select="count(r[position()=1]/c) + 1" /></xsl:otherwise>
					</xsl:choose>
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>

		
		<xsl:variable name="sum_of_values" select="@sum" />
		
		
		<xsl:variable name="norm_factor">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="@sum" /></xsl:when>
				<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="@max" /></xsl:when>
				<xsl:otherwise>100</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		

		<paragraph>
		
			
			<!-- Create element "table"-->
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$pocet_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$pocet_radku" /></xsl:attribute>
				
				<xsl:variable name="attr_id" select="@attributes" />
				<xsl:variable name="attr_name" select="key('key_ti_attribute',@attributes)/@quant" />

				
				<xsl:for-each select="r">
					
					<xsl:variable name="pocet_polozek" select="count(c)"/>  <!-- pocet datovych polozek v tabulce-->
					
					<!-- Horisontal table-->
					
					<xsl:if test="$TablePosition='Horisontal'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d0" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d0text"><xsl:value-of select="$label_cat" /> - <xsl:value-of select="$attr_name" /></text> 
							</td>
							
							
							
							<xsl:for-each select="key('key_ti_attribute',$attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r1d<xsl:value-of select="position()" />
									</xsl:attribute>
									
									<xsl:attribute name="border_right">
										<xsl:choose>
											<xsl:when test="$pocet_polozek=position()"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_top"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									
									<text id="{$id_base}r1d{position()}text"><xsl:value-of select="@value" /></text> 
								</xsl:element>
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<td id="{$id_base}r1d_sum" border_left="{$bord_frm}" border_right="{$bord_out}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
									<text id="{$id_base}r1d_sum_text"><xsl:value-of select="$label_sum" /></text> 
								</td>
							</xsl:if>
						</tr>
						
						<tr id="{$id_base}r2">
							<td id="{$id_base}r2d0" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_out}">
								<text id="{$id_base}r1d0text">
									<xsl:value-of select="$label_freq" />
									<xsl:if test="$TypeOfValues!='abs'">
										<xsl:text> (%)</xsl:text>
									</xsl:if>
								</text> 
							</td>
							
							
							
							<xsl:for-each select="c">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r2d<xsl:value-of select="position()" />
									</xsl:attribute>
									<xsl:if test="$ColorHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values))" />
										</xsl:attribute>
									</xsl:if>
									
									<xsl:attribute name="border_right">
										<xsl:choose>
											<xsl:when test="$pocet_polozek=position()"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
									
									<xsl:variable name="hodnota">
										<xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor))" />
									</xsl:variable>
									
									<text id="{$id_base}r1d{position()}text"><xsl:value-of select="$hodnota"/></text> 
									
								</xsl:element>
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<td id="{$id_base}r2d_sum" border_left="{$bord_frm}" border_right="{$bord_out}"  border_bottom="{$bord_out}">
									<text id="{$id_base}r2d_sum_text"><xsl:value-of select="$sum_of_values" /></text> 
								</td>
							</xsl:if>
						</tr>
					</xsl:if>
					
					
					
					
					<!-- Vertical table-->
					
					<xsl:if test="$TablePosition='Vertical'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d1text"><xsl:value-of select="$label_cat" /> - <xsl:value-of select="$attr_name" /></text> 
							</td>
							<td id="{$id_base}r1d2" bgcolor="{$border_color}" border_right="{$bord_out}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d2text">
									<xsl:value-of select="$label_freq" />
									<xsl:if test="$TypeOfValues='Relative'">
										<xsl:text> (%)</xsl:text>
									</xsl:if>
								</text> 
							</td>							
						</tr>
						
						
						<xsl:for-each select="c">
							<xsl:variable name="pozice" select="position()" />
							<tr id="{$id_base}r{position()}">
								
								
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d1text</xsl:text>
									</xsl:attribute>
									<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$pocet_polozek=position()"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_left"><xsl:value-of select="$bord_out"/></xsl:attribute>
									
									<text id="{$id_base}r{position()}d1text">
										<xsl:value-of select="key('key_ti_attribute',$attr_id)/ti_category[position()=position()]/@value" />
									</text>
								</xsl:element>
								
								
								
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d2</xsl:text>
									</xsl:attribute>
									<xsl:if test="$ColorHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values))" />
										</xsl:attribute>
									</xsl:if>
									
									<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$pocet_polozek=position()"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
									
									<xsl:variable name="hodnota">
										<xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor))" />
									</xsl:variable>
									
									<text id="{$id_base}r{position()}d2text"><xsl:value-of select="$hodnota"/></text> 
								</xsl:element>	
								
							</tr>
						</xsl:for-each>
						
						<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
							<tr id="{$id_base}r_sum">
								<td id="{$id_base}r_sum_d1" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_frm}" border_bottom="{$bord_out}">
									<text id="{$id_base}r_sum_d1text"><xsl:value-of select="$label_sum"/></text>
								</td>
								
								<td id="{$id_base}r_sum_d2" border_right="{$bord_out}" border_top="{$bord_frm}" border_bottom="{$bord_out}">
									<text id="{$id_base}r_sum_d2text">
										<xsl:value-of select="$sum_of_values" />
									</text>
								</td>
							</tr>
						</xsl:if>
						
						
					</xsl:if>
				   
				
				
				</xsl:for-each>
							
			</xsl:element>
		
		
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}tab_desc">
					<br/>
					<xsl:text>Tab:</xsl:text>
					<tab/>
					<br/>
				</text>
			</xsl:if>


		
		</paragraph>
		
		


	</xsl:template>
	




</xsl:stylesheet>
