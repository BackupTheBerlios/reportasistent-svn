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


    function des_tecka(n)
	{
		return (n.replace(",","."));
	}
	
	
	function hodnota(val1, val2, nf1, nf2, nf)
	{
		var delitel1 = nf1;
		if (delitel1 == 0)
			delitel1 = 1;
		var delitel2 = nf2;
		if (delitel2 == 0)
			delitel2 = 1;
		var delitel = nf;
		if (delitel == 0)
			delitel = 1;
		
		return (Math.round(Math.abs((val1/delitel1) - (val2/delitel2)) / delitel));
	}
	
	function podel(x,y)
	{
		if (y == 0)
			return (0);
		return (x/y);
	}

  </msxsl:script>


<!-- klic - atributy-->
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />
<!-- klic - hypotezy -->
<xsl:key name="key_hyp_sdcf" match="hyp_sdcf" use="@id" />	

<!-- Promenne - nastaveni vizualizaci-->


<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="TabLegend">Tab:</xsl:variable>
<xsl:variable name="TypeOfValues">rel_sum</xsl:variable>
<xsl:variable name="DifType">dif_abs</xsl:variable>
<xsl:variable name="BorderHighlight">true</xsl:variable>
<xsl:variable name="BorderColor">#eeeeee</xsl:variable>
<xsl:variable name="BorderOutWidth">225e-2</xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
<xsl:variable name="BorderInWidth">0</xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
<xsl:variable name="BorderFrmWidth">1</xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
<xsl:variable name="TablePosition">Vertical</xsl:variable>
  

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
		<xsl:when test="$lng='cz'">Rozdíl frekv.</xsl:when>
		<xsl:when test="$lng='en'">Difference of freq.</xsl:when>
		<xsl:otherwise>Difference of freq.</xsl:otherwise>
	</xsl:choose>
</xsl:variable>


    
    
    
    <!-- nastaveni tloustky ohraniceni-->
		
	<xsl:variable name="bord_out"><xsl:value-of select="$BorderOutWidth"/></xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
	<xsl:variable name="bord_in"><xsl:value-of select="$BorderInWidth"/></xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
	<xsl:variable name="bord_frm"><xsl:value-of select="$BorderFrmWidth"/></xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->

    
    
    
<!-- TEMPLATES -->


      



	<xsl:template match="hyp_sdcf">
		
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
					<xsl:value-of select="count(r[position()=1]/c) + 1" />
				</xsl:when>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="pocet_sloupcu">
			<xsl:choose>
				<xsl:when test="$TablePosition='Vertical'">
					<xsl:text>2</xsl:text>
				</xsl:when>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:value-of select="count(r[position()=1]/c) + 1" />
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>

		

		
		<xsl:variable name="norm_factor">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='rel_sum'">
					<xsl:choose>
						<xsl:when test="$DifType='dif_abs'"><xsl:value-of select="number(@da_sum) div 100"/></xsl:when>
						<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="dedek:des_tecka(string(@dr_sum))"/></xsl:when>
					</xsl:choose>
				</xsl:when>
				
				<xsl:when test="$TypeOfValues='rel_max'">
					<xsl:choose>
						<xsl:when test="$DifType='dif_abs'"><xsl:value-of select="number(@da_max) div 100"/></xsl:when>
						<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="dedek:des_tecka(string(@dr_max))"/></xsl:when>
					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>1</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="norm_factor_set1">
			<xsl:choose>
				<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="number(@sum1) div 100"/></xsl:when>
				<xsl:otherwise>1</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="norm_factor_set2">
			<xsl:choose>
				<xsl:when test="$DifType='dif_rel'"><xsl:value-of select="number(@sum2) div 100"/></xsl:when>
				<xsl:otherwise>1</xsl:otherwise>
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

				
				<xsl:for-each select="r[position()=1]">
					
					<xsl:variable name="pocet_polozek" select="count(c)"/>  <!-- pocet datovych polozek v tabulce-->
					
					<!-- Horisontal table-->
					
					<xsl:if test="$TablePosition='Horisontal'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d0" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d0text"><xsl:value-of select="$attr_name" /></text> 
							</td>
							
							
							
							<xsl:for-each select="key('key_ti_attribute',$attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r1d<xsl:value-of select="position()" />
									</xsl:attribute>
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="$border_color" />
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
									<xsl:attribute name="border_right">
										<xsl:choose>
											<xsl:when test="$pocet_polozek=position()"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
									
									<xsl:variable name="pozice" select="position()"/>
									<xsl:variable name="val1" select="@val"/>
									<xsl:variable name="val2" select="key('key_hyp_sdcf',$id_base)/r[position()=2]/c[position()=$pozice]/@val"/>
									<xsl:variable name="hodnota">
										<xsl:value-of select="dedek:hodnota(number($val1),number($val2),number($norm_factor_set1),number($norm_factor_set2),number($norm_factor))"/>
									</xsl:variable>
									
									<text id="{$id_base}r1d{position()}text"><xsl:value-of select="$hodnota"/></text> 
									
								</xsl:element>
							</xsl:for-each>
							
						</tr>
					</xsl:if>
					
					
					
					
					<!-- Vertical table-->
					
					<xsl:if test="$TablePosition='Vertical'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d1text"><xsl:value-of select="$attr_name" /></text> 
							</td>
							<td id="{$id_base}r1d2" bgcolor="{$border_color}" border_right="{$bord_out}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d2text">
									<xsl:value-of select="$label_freq" />
									<xsl:if test="$TypeOfValues!='abs'">
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
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="$border_color" />
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
										<xsl:value-of select="key('key_ti_attribute',$attr_id)/ti_category[position()=$pozice]/@value" />
									</text>
								</xsl:element>
								
								
								
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d2</xsl:text>
									</xsl:attribute>
									
									<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$pocet_polozek=position()"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
									
									
									
									<xsl:variable name="pozice2" select="position()"/>
									<xsl:variable name="val1" select="@val"/>
									<xsl:variable name="val2" select="key('key_hyp_sdcf',$id_base)/r[position()=2]/c[position()=$pozice2]/@val"/>
									<xsl:variable name="hodnota">
										<xsl:value-of select="dedek:hodnota(number($val1),number($val2),number($norm_factor_set1),number($norm_factor_set2),number($norm_factor))"/>
									</xsl:variable>
									
									
									<text id="{$id_base}r{position()}d2text"><xsl:value-of select="$hodnota"/></text> 
								</xsl:element>	
								
							</tr>
						</xsl:for-each>
						
						
						
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
