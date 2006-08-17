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
<!-- klic - hypotezy-->
<xsl:key name="key_hyp_sdcf" match="hyp_sdcf" use="@id" />



<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="FirstSetShow">true</xsl:variable>
<xsl:variable name="SecondSetShow">true</xsl:variable>
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

<xsl:variable name="label_cat">   <!-- nadpis tabulky: Category-->
	<xsl:choose>
		<xsl:when test="$lng='cz'">Kategorie</xsl:when>
		<xsl:when test="$lng='en'">Category</xsl:when>
		<xsl:otherwise>Category</xsl:otherwise>
	</xsl:choose>
</xsl:variable>

<xsl:variable name="label_freq">   <!-- nadpis tabulky: frekvence-->
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



      

<xsl:template match="hyp_sdcf">

	<xsl:if test="$FirstSetShow='true' or $SecondSetShow='true'">
	

		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderHighlight='true'"><xsl:value-of select="$BorderColor" /></xsl:when>
				<xsl:otherwise></xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		
		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="hyp_id" select="@id" />
		
		<xsl:variable name="pocet_radku">
			<xsl:choose>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:choose>
						<xsl:when test="$FirstSetShow='true' and $SecondSetShow='true'">3</xsl:when>
						<xsl:otherwise>2</xsl:otherwise>
					</xsl:choose>
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
					<xsl:choose>
						<xsl:when test="$FirstSetShow='true' and $SecondSetShow='true'">3</xsl:when>
						<xsl:otherwise>2</xsl:otherwise>
					</xsl:choose>
				</xsl:when>
				<xsl:when test="$TablePosition='Horisontal'">
					<xsl:choose>
						<xsl:when test="$SumShow='true' and $TypeOfValues='abs'"><xsl:value-of select="count(r[position()=1]/c) + 2" /></xsl:when>
						<xsl:otherwise><xsl:value-of select="count(r[position()=1]/c) + 1" /></xsl:otherwise>
					</xsl:choose>
				</xsl:when>
			</xsl:choose>		
		</xsl:variable>


		
		<xsl:variable name="sum_of_values_set1" select="@sum1" />
		<xsl:variable name="sum_of_values_set2" select="@sum2" />
		
		<xsl:variable name="norm_factor_set1">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="@sum1" /></xsl:when>
				<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="@max1" /></xsl:when>
				<xsl:otherwise>100</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="norm_factor_set2">
			<xsl:choose>
				<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="@sum2" /></xsl:when>
				<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="@max2" /></xsl:when>
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

				<xsl:variable name="pocet_polozek" select="count(key('key_ti_attribute',$attr_id)/ti_category)"/>
				
					
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
									<xsl:attribute name="bgcolor"><xsl:value-of select="$border_color" /></xsl:attribute>
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
								<td id="{$id_base}r1d_sum" bgcolor="{$border_color}" border_left="{$bord_frm}" border_right="{$bord_out}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
									<text id="{$id_base}r1d_sum_text"><xsl:value-of select="$label_sum" /></text> 
								</td>
							</xsl:if>
						</tr>
						
						<xsl:for-each select="r">
				
						  <xsl:variable name="cislo_radku" select="position()" />
						  <xsl:if test="($cislo_radku='1' and $FirstSetShow='true') or ($cislo_radku='2' and $SecondSetShow='true')">
						  
						  <xsl:variable name="norm_factor">
						  	<xsl:choose>
						  		<xsl:when test="$cislo_radku='1'"><xsl:value-of select="$norm_factor_set1"/></xsl:when>
						  		<xsl:when test="$cislo_radku='2'"><xsl:value-of select="$norm_factor_set2"/></xsl:when>
						  		<xsl:otherwise>100</xsl:otherwise>
						  	</xsl:choose>
						  </xsl:variable>
						  
						  <xsl:variable name="sum_of_values">
						  	<xsl:choose>
						  		<xsl:when test="$cislo_radku='1'"><xsl:value-of select="$sum_of_values_set1"/></xsl:when>
						  		<xsl:when test="$cislo_radku='2'"><xsl:value-of select="$sum_of_values_set2"/></xsl:when>
						  		<xsl:otherwise>100</xsl:otherwise>
						  	</xsl:choose>
						  </xsl:variable>
						
					    	<tr id="{$id_base}r{$cislo_radku}">
								
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base"/><xsl:text>r</xsl:text><xsl:value-of select="$cislo_radku"/><xsl:text>d0</xsl:text>
									</xsl:attribute>
									<xsl:attribute name="bgcolor"><xsl:value-of select="$border_color"/></xsl:attribute>
									<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$cislo_radku='2' or ($cislo_radku='1' and $SecondSetShow='false')"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<xsl:attribute name="border_left"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<text id="{$id_base}r{$cislo_radku}d0text">
										<xsl:if test="$cislo_radku='1'">
											<xsl:value-of select="$label_item1" />
										</xsl:if>
										<xsl:if test="$cislo_radku='2'">
											<xsl:value-of select="$label_item2" />
										</xsl:if>
										<xsl:if test="$TypeOfValues!='abs'">
											<xsl:text> (%)</xsl:text>
										</xsl:if>
									</text> 
								</xsl:element>
								
								
								
								
								<xsl:for-each select="c">
									<xsl:element name="td">
										<xsl:attribute name="id">
											<xsl:value-of select="$id_base" />r<xsl:value-of select="$cislo_radku" />d<xsl:value-of select="position()" />
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
										<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$cislo_radku='2' or ($cislo_radku='1' and $SecondSetShow='false')"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
										
										<xsl:variable name="hodnota">
											<xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor))" />
										</xsl:variable>
										
										<text id="{$id_base}r1d{position()}text"><xsl:value-of select="$hodnota"/></text> 
										
									</xsl:element>
								</xsl:for-each>
							
								<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								
									<xsl:element name="td">
										<xsl:attribute name="id">
											<xsl:value-of select="$id_base"/><xsl:text>r</xsl:text><xsl:value-of select="$cislo_radku"/><xsl:text>d_sum</xsl:text>
										</xsl:attribute>
										
										<xsl:attribute name="border_bottom">
											<xsl:choose>
												<xsl:when test="$cislo_radku='2' or ($cislo_radku='1' and $SecondSetShow='false')"><xsl:value-of select="$bord_out"/></xsl:when>
												<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
											</xsl:choose>
										</xsl:attribute>
										<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
										<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
										<text id="{$id_base}r{$cislo_radku}d_sum_text"><xsl:value-of select="$sum_of_values" /></text> 
									</xsl:element>
										
									
								</xsl:if>
								
								
							</tr>
						
						  </xsl:if>	
						  
						</xsl:for-each>	<!-- for-each "r"-->
						
					</xsl:if>
					
						
					
					<!-- Vertical table-->
					
					<xsl:if test="$TablePosition='Vertical'">
						<tr id="{$id_base}r1">
							<td id="{$id_base}r1d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_out}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r1d1text"><xsl:value-of select="$attr_name"/></text> 
							</td>
							
							<xsl:if test="$FirstSetShow='true'">
								<xsl:element name="td">
									<xsl:attribute name="id"><xsl:value-of select="$id_base" />r1d2</xsl:attribute>
									<xsl:attribute name="bgcolor"><xsl:value-of select="$border_color" /></xsl:attribute>
									<xsl:attribute name="border_top"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_right">
										<xsl:choose>
											<xsl:when test="$SecondSetShow='false'"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									<text id="{$id_base}r1d2text">
										<xsl:value-of select="$label_item1" />
										<xsl:if test="$TypeOfValues!='abs'">
											<xsl:text> (%)</xsl:text>
										</xsl:if>
									</text> 
								</xsl:element>
							</xsl:if>
								
							<xsl:if test="$SecondSetShow='true'">
								<xsl:element name="td">
									<xsl:attribute name="id"><xsl:value-of select="$id_base" />r1d2</xsl:attribute>
									<xsl:attribute name="bgcolor"><xsl:value-of select="$border_color" /></xsl:attribute>
									<xsl:attribute name="border_top"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<text id="{$id_base}r1d3text">
										<xsl:value-of select="$label_item2" />
										<xsl:if test="$TypeOfValues!='abs'">
											<xsl:text> (%)</xsl:text>
										</xsl:if>
									</text> 
								</xsl:element>	
							</xsl:if>
									
						</tr>
	
											
						
							<xsl:for-each select="r[position()=1]/c">
								<xsl:variable name="pozice" select="position()" />
								<tr id="{$id_base}r{position()}">
									
									<xsl:element name="td">
										<xsl:attribute name="id">
											<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d1</xsl:text>
										</xsl:attribute>
										<xsl:attribute name="bgcolor"><xsl:value-of select="$border_color" /></xsl:attribute>
										<xsl:attribute name="border_left"><xsl:value-of select="$bord_out"/></xsl:attribute>
										<xsl:attribute name="border_bottom">
											<xsl:choose>
												<xsl:when test="$pozice=$pocet_polozek"><xsl:value-of select="$bord_out"/></xsl:when>
												<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
											</xsl:choose>
										</xsl:attribute>
										<xsl:attribute name="border_right"><xsl:value-of select="$bord_frm"/></xsl:attribute>
										<text id="{$id_base}r{position()}d1text">
											<xsl:value-of select="key('key_ti_attribute',$attr_id)/ti_category[position()=$pozice]/@value" />
										</text>
									</xsl:element>
									
	
									<xsl:if test="$FirstSetShow='true'">						
										<xsl:element name="td">
											<xsl:attribute name="id">
												<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d2</xsl:text>
											</xsl:attribute>
											<xsl:if test="$ColorHighlighting='true'">
												<xsl:attribute name="bgcolor">
													<xsl:value-of select="dedek:RGB(number(@val), number($sum_of_values_set1))" />
												</xsl:attribute>
											</xsl:if>
											
											<xsl:attribute name="border_right">
												<xsl:choose>
													<xsl:when test="$SecondSetShow='false'"><xsl:value-of select="$bord_out"/></xsl:when>
													<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
												</xsl:choose>
											</xsl:attribute>
											
											<xsl:attribute name="border_bottom">
												<xsl:choose>
													<xsl:when test="$pozice=$pocet_polozek"><xsl:value-of select="$bord_out"/></xsl:when>
													<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
												</xsl:choose>
											</xsl:attribute>
											
											<text id="{$id_base}r{position()}d2text">
												<xsl:value-of select="dedek:normalize_value(number(@val), number($norm_factor_set1))" />
											</text> 
										</xsl:element>
									</xsl:if>
									
									<xsl:if test="$SecondSetShow='true'">
										<xsl:element name="td">
											<xsl:attribute name="id">
												<xsl:value-of select="$id_base" />r<xsl:value-of select="position()" /><xsl:text>d3</xsl:text>
											</xsl:attribute>
											
											<xsl:variable name="val" select="key('key_hyp_sdcf',$hyp_id)/r[position()=2]/c[position()=$pozice]/@val" />
											
											<xsl:if test="$ColorHighlighting='true'">
												<xsl:attribute name="bgcolor">
													<xsl:value-of select="dedek:RGB(number($val), number($sum_of_values_set2))" />
												</xsl:attribute>
											</xsl:if>
											
											<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
											
											
											<xsl:attribute name="border_bottom">
												<xsl:choose>
													<xsl:when test="$pozice=$pocet_polozek"><xsl:value-of select="$bord_out"/></xsl:when>
													<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
												</xsl:choose>
											</xsl:attribute>
											
											<text id="{$id_base}r{position()}d3text">
												<xsl:value-of select="dedek:normalize_value(number($val), number($norm_factor_set2))" />
											</text> 
										</xsl:element>	
									</xsl:if>
									
									
								</tr>
							</xsl:for-each>
						
							<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<tr id="{$id_base}r_sum">
									<td id="{$id_base}r_sum_d1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}"  border_bottom="{$bord_out}" border_top="{$bord_frm}">
										<text id="{$id_base}r_sum_d1text"><xsl:value-of select="$label_sum" /></text>
									</td>
									
									<xsl:if test="$FirstSetShow='true'">
										<xsl:element name="td">
											<xsl:attribute name="id">
												<xsl:value-of select="$id_base" /><xsl:text>r_sum_d2</xsl:text>
											</xsl:attribute>
											<xsl:attribute name="border_right">
												<xsl:choose>
													<xsl:when test="$SecondSetShow='false'"><xsl:value-of select="$bord_out"/></xsl:when>
													<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
												</xsl:choose>
											</xsl:attribute>
											<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
											<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>
											<text id="{$id_base}r_sum_d2text">
												<xsl:value-of select="$sum_of_values_set1" />
											</text>
										</xsl:element>
									</xsl:if>
									
									<xsl:if test="$SecondSetShow='true'">
										<td id="{$id_base}r_sum_d3" border_left="{$bord_in}" border_right="{$bord_out}"  border_bottom="{$bord_out}" border_top="{$bord_frm}">
											<text id="{$id_base}r_sum_d3text">
												<xsl:value-of select="$sum_of_values_set2" />
											</text>
										</td>
									</xsl:if>
										
										
								</tr>
							</xsl:if>
						
						
						
					</xsl:if>
					
				   
				
				
				
							
			</xsl:element>
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text>
					<br/>
					<xsl:value-of select="$TabLegend"/>
					<br/>
				</text>
			</xsl:if>

		
		</paragraph>


		
	</xsl:if>


</xsl:template>
	




</xsl:stylesheet>
