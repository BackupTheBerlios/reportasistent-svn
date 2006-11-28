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
		var delitel = cim;
		if (delitel == 0)
			delitel = 1;
		return Math.round(100*(co/delitel));
	}

  </msxsl:script>


<!-- klic - atributy-->
<xsl:key name="key_ti_attribute" match="ti_attribute" use="@id" />

<!-- klic - hypotezy (Kody: kvuli pocitani sum sloupcu - mozna zkusit najit lepsi reseni)-->
<xsl:key name="key_hyp_sdkl" match="hyp_sdkl" use="@id" />


<!-- Promenne - nastaveni vizualizaci-->
<xsl:variable name="FirstSetShow">true</xsl:variable>
<xsl:variable name="SecondSetShow">true</xsl:variable>
<xsl:variable name="SumShow">true</xsl:variable>
<xsl:variable name="ShowLegend">true</xsl:variable>
<xsl:variable name="TabLegend">Tab:</xsl:variable>
<xsl:variable name="ColorHighlighting">true</xsl:variable>
<xsl:variable name="TypeOfValues">rel_max</xsl:variable>
<xsl:variable name="BorderHighlight">true</xsl:variable>
<xsl:variable name="BorderColor">#eeeeee</xsl:variable>
<xsl:variable name="BorderOutWidth">225e-2</xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
<xsl:variable name="BorderInWidth">0</xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
<xsl:variable name="BorderFrmWidth">1</xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->







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


<!-- nastaveni tloustky ohraniceni-->
		
	<xsl:variable name="bord_out"><xsl:value-of select="$BorderOutWidth"/></xsl:variable> <!-- tloustka ohraniceni vnejsku tabulky-->
	<xsl:variable name="bord_in"><xsl:value-of select="$BorderInWidth"/></xsl:variable>	<!-- tloustka ohraniceni oddelovace hlavicky tabulky-->
	<xsl:variable name="bord_frm"><xsl:value-of select="$BorderFrmWidth"/></xsl:variable> <!-- tloustka ohraniceni ciselnych policek tabulky-->
		


    
<!-- TEMPLATES -->



      

<xsl:template match="hyp_sdkl">

	<xsl:if test="$FirstSetShow='true' or $SecondSetShow='true'">

		<xsl:variable name="border_color">
			<xsl:choose>
				<xsl:when test="$BorderHighlight='true'"><xsl:value-of select="$BorderColor" /></xsl:when>
				<xsl:otherwise></xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="id_base" select="@id" />
		
		<xsl:variable name="pocet_radku">
			<xsl:choose>
				<xsl:when test="$SumShow='true' and $TypeOfValues='abs'"><xsl:value-of select="count(tab[position()=1]/r) + 2" /></xsl:when>
				<xsl:otherwise><xsl:value-of select="count(tab[position()=1]/r) + 1" /></xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="pocet_sloupcu">
			<xsl:choose>
				<xsl:when test="$FirstSetShow='true' and $SecondSetShow='true'">
					<xsl:choose>
						<xsl:when test="$SumShow='true' and $TypeOfValues='abs'"><xsl:value-of select="2 * (count(tab[position()=1]/r[position()=1]/c) + 2) + 1" /></xsl:when>
						<xsl:otherwise><xsl:value-of select="2 * (count(tab[position()=1]/r[position()=1]/c) + 1) + 1" /></xsl:otherwise>
					</xsl:choose>
				</xsl:when>
				<xsl:otherwise>
					<xsl:choose>
						<xsl:when test="$SumShow='true' and $TypeOfValues='abs'"><xsl:value-of select="count(tab[position()=1]/r[position()=1]/c) + 2" /></xsl:when>
						<xsl:otherwise><xsl:value-of select="count(tab[position()=1]/r[position()=1]/c) + 1" /></xsl:otherwise>
					</xsl:choose>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		
		<xsl:variable name="sum_of_values_set1" select="@sum1" />
		<xsl:variable name="max_value_set1" select="@max1" />
		<xsl:variable name="sum_of_values_set2" select="@sum2" />
		<xsl:variable name="max_value_set2" select="@max2" />
		
		
		<xsl:variable name="row_attr_id">
			<xsl:value-of select="@row_attributes" />
		</xsl:variable>
		
			<xsl:variable name="col_attr_id">
			<xsl:value-of select="@column_attributes" />
		</xsl:variable>
		
		<xsl:variable name="row_attr_name">
			<xsl:value-of select="key('key_ti_attribute',$row_attr_id)/@quant" />
		</xsl:variable>
		
		<xsl:variable name="col_attr_name">
			<xsl:value-of select="key('key_ti_attribute',$col_attr_id)/@quant" />
		</xsl:variable>
		
		<xsl:variable name="pocet_kat_row" select="count(key('key_ti_attribute',$row_attr_id)/ti_category)"/>
		<xsl:variable name="pocet_kat_col" select="count(key('key_ti_attribute',$col_attr_id)/ti_category)"/>
		
	
		
		<xsl:variable name="hyp_id" select="@id" />

		<paragraph>
			
			<!-- Create element "table"-->
			<xsl:element name="table" >
			    <xsl:attribute name="id"><xsl:value-of select="$id_base"/>table1</xsl:attribute>
			    <xsl:attribute name="cols"><xsl:value-of select="$pocet_sloupcu" /></xsl:attribute>
			    <xsl:attribute name="rows"><xsl:value-of select="$pocet_radku" /></xsl:attribute>
				
				
				<!-- first row of table-->
				<tr id="{$id_base}r0">
					<xsl:if test="$FirstSetShow='true'">
					
							<td id="{$id_base}r0d0" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r0d0text">
								<xsl:value-of select="$row_attr_name"/><xsl:text> \ </xsl:text><xsl:value-of select="$col_attr_name"/><xsl:text> - </xsl:text><xsl:value-of select="$label_first_set"/>
								<xsl:if test="$TypeOfValues!='abs'"> (%)</xsl:if> 
								</text> 
							</td>
							
							<xsl:for-each select="key('key_ti_attribute',$col_attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r0d<xsl:value-of select="position()" />
									</xsl:attribute>
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="$border_color" />
									</xsl:attribute>
									
									<xsl:attribute name="border_top"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_right">
										<xsl:choose>
											<xsl:when test="position()=$pocet_kat_col"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>

									<text id="{$id_base}r0d{position()}text"><xsl:value-of select="@value" /></text> 
								</xsl:element>	
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<td id="{$id_base}r0d_sum" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_frm}" border_right="{$bord_out}" border_bottom="{$bord_frm}">
									<text id="{$id_base}r0d_sum_text"><xsl:value-of select="$label_sum" /></text>
								</td>
							</xsl:if>
							
							<xsl:if test="$SecondSetShow='true'">
								<td id="{$id_base}r0mezera"/>
							</xsl:if>
							
					</xsl:if>   <!-- FirstSetShow-->
					
					<xsl:if test="$SecondSetShow='true'">
					
							<td id="{$id_base}r0d0" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_out}" border_right="{$bord_frm}" border_bottom="{$bord_frm}">
								<text id="{$id_base}r0d0text">
								<xsl:value-of select="$row_attr_name"/><xsl:text> \ </xsl:text><xsl:value-of select="$col_attr_name"/><xsl:text> - </xsl:text><xsl:value-of select="$label_second_set"/>
								<xsl:if test="$TypeOfValues!='abs'"> (%)</xsl:if> 
								</text> 
							</td>
							
							<xsl:for-each select="key('key_ti_attribute',$col_attr_id)/ti_category">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base" />r0d<xsl:value-of select="position()" />
									</xsl:attribute>
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="$border_color" />
									</xsl:attribute>
									
									<xsl:attribute name="border_top"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_right">
										<xsl:choose>
											<xsl:when test="position()=$pocet_kat_col"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>

									<text id="{$id_base}r0d{position()}text"><xsl:value-of select="@value" /></text> 
								</xsl:element>	
							</xsl:for-each>
							
							<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<td id="{$id_base}r0d_sum" bgcolor="{$border_color}" border_top="{$bord_out}" border_left="{$bord_frm}" border_right="{$bord_out}" border_bottom="{$bord_frm}">
									<text id="{$id_base}r0d_sum_text"><xsl:value-of select="$label_sum" /></text>
								</td>
							</xsl:if>
							
					</xsl:if>   <!-- SecondSetShow-->
					
					
				</tr>
				
				
				<!-- further rows of table -->
				
				<xsl:for-each select="tab[position()=1]/r">
					<xsl:variable name="row_number" select="position()" />
					<xsl:variable name="row_values_sum_set1" select="sum(c/@val)" />  <!-- sum of values in this row -->
					<xsl:variable name="row_values_sum_set2" select="sum(key('key_hyp_sdkl',$id_base)/tab[position()=2]/r[position()=$row_number]/c/@val)"/>
					
					
					<tr id="{$id_base}r{$row_number}">
					
					  <xsl:if test="$FirstSetShow='true'">	
					  
						<xsl:element name="td">
							<xsl:attribute name="id">
								<xsl:value-of select="$id_base" /><xsl:text>r</xsl:text><xsl:value-of select="$row_number" /><xsl:text>d0set1</xsl:text>
							</xsl:attribute>
							
							<xsl:if test="$BorderHighlight='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="$border_color" />
								</xsl:attribute>
							</xsl:if>

							<xsl:attribute name="border_left"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_bottom">
								<xsl:choose>
									<xsl:when test="position()=$pocet_kat_row"><xsl:value-of select="$bord_out"/></xsl:when>
									<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
								</xsl:choose>
							</xsl:attribute>
							
							<text id="{$id_base}r{$row_number}d0textset1">
									<xsl:value-of select="key('key_ti_attribute',$row_attr_id)/ti_category[position()=$row_number]/@value" />
							</text> 
							
						</xsl:element>
						
						
						
						
						<xsl:for-each select="c">
							<xsl:variable name="col_number_set1" select="position()" />
							
							<xsl:variable name="norm_factor_set1">  <!-- normalizacni faktor-->
								<xsl:choose>
									<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="$sum_of_values_set1"/></xsl:when>
									<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="$max_value_set1"/></xsl:when>
									<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="$row_values_sum_set1"/></xsl:when>
									<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="sum(key('key_hyp_sdkl',$hyp_id)/tab[position()=1]/r/c[position()=$col_number_set1]/@val)"/></xsl:when>
									<xsl:otherwise>100</xsl:otherwise>
								</xsl:choose>
							</xsl:variable>

              <xsl:variable name="color_norm_factor_set1">
                <xsl:choose>
                  <xsl:when test="$TypeOfValues='abs'">
                    <xsl:value-of select="$sum_of_values_set1"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$norm_factor_set1"/>
                  </xsl:otherwise>
                </xsl:choose>
              </xsl:variable>
							
							<xsl:element name="td">
								<xsl:attribute name="id">
									<xsl:value-of select="$id_base" />r<xsl:value-of select="$row_number" />d<xsl:value-of select="$col_number_set1" /><xsl:text>set1</xsl:text>
								</xsl:attribute>
								
								<xsl:if test="$ColorHighlighting='true'">
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="dedek:RGB(number(@val), number($color_norm_factor_set1))" />
                    <!--2. parametr byl $sum_of_values_set1-->
									</xsl:attribute>
								</xsl:if>
								
								<xsl:attribute name="border_right">
									<xsl:choose>
										<xsl:when test="position()=$pocet_kat_col"><xsl:value-of select="$bord_out"/></xsl:when>
										<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
									</xsl:choose>
								</xsl:attribute>
								<xsl:attribute name="border_bottom">
									<xsl:choose>
										<xsl:when test="$row_number=$pocet_kat_row"><xsl:value-of select="$bord_out"/></xsl:when>
										<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
									</xsl:choose>
								</xsl:attribute>
								
								<text id="{$id_base}r{$row_number}d{$col_number_set1}textset1">
									<xsl:value-of select="dedek:normalize_value(number(@val),number($norm_factor_set1))"/>
								</text> 
							</xsl:element>	
							
						</xsl:for-each>
						
						<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base"/>r<xsl:value-of select="$row_number"/><xsl:text>d_sumset1</xsl:text>
									</xsl:attribute>
									
									<!-- Kody - policka se souctem se nehighlightuji
                  <xsl:if test="$ColorHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number($row_values_sum_set1), number($sum_of_values_set1))" />
										</xsl:attribute>
									</xsl:if>-->
									
									<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$row_number=$pocet_kat_row"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									
									<text id="{$id_base}r{$row_number}d_sum_textset1">
										<xsl:value-of select="$row_values_sum_set1" />
									</text>
								</xsl:element>
						</xsl:if>
						<xsl:if test="$SecondSetShow='true'">
							<td id="{$id_base}r{$row_number}mezera"/>
						</xsl:if>
					  
					  </xsl:if>  <!-- First set show-->
					  
					  <xsl:if test="$SecondSetShow='true'">
					  
					  	<xsl:element name="td">
							<xsl:attribute name="id">
								<xsl:value-of select="$id_base" /><xsl:text>r</xsl:text><xsl:value-of select="$row_number" /><xsl:text>d0set2</xsl:text>
							</xsl:attribute>
							
							<xsl:if test="$BorderHighlight='true'">
								<xsl:attribute name="bgcolor">
									<xsl:value-of select="$border_color" />
								</xsl:attribute>
							</xsl:if>

							<xsl:attribute name="border_left"><xsl:value-of select="$bord_out"/></xsl:attribute>
							<xsl:attribute name="border_right"><xsl:value-of select="$bord_frm"/></xsl:attribute>
							<xsl:attribute name="border_bottom">
								<xsl:choose>
									<xsl:when test="position()=$pocet_kat_row"><xsl:value-of select="$bord_out"/></xsl:when>
									<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
								</xsl:choose>
							</xsl:attribute>
							
							<text id="{$id_base}r{$row_number}d0textset2">
									<xsl:value-of select="key('key_ti_attribute',$row_attr_id)/ti_category[position()=$row_number]/@value" />
							</text> 
							
						</xsl:element>
						
						
						
						
						<xsl:for-each select="key('key_hyp_sdkl',$hyp_id)/tab[position()=2]/r[position()=$row_number]/c">
							<xsl:variable name="col_number_set2" select="position()" />
							
							<xsl:variable name="norm_factor_set2">  <!-- normalizacni faktor-->
								<xsl:choose>
									<xsl:when test="$TypeOfValues='rel_sum'"><xsl:value-of select="$sum_of_values_set2"/></xsl:when>
									<xsl:when test="$TypeOfValues='rel_max'"><xsl:value-of select="$max_value_set2"/></xsl:when>
									<xsl:when test="$TypeOfValues='rel_row'"><xsl:value-of select="$row_values_sum_set2"/></xsl:when>
									<xsl:when test="$TypeOfValues='rel_col'"><xsl:value-of select="sum(key('key_hyp_sdkl',$hyp_id)/tab[position()=2]/r/c[position()=$col_number_set2]/@val)"/></xsl:when>
									<xsl:otherwise>100</xsl:otherwise>
								</xsl:choose>
							</xsl:variable>

              <xsl:variable name="color_norm_factor_set2">
                <xsl:choose>
                  <xsl:when test="$TypeOfValues='abs'">
                    <xsl:value-of select="$sum_of_values_set2"/>
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="$norm_factor_set2"/>
                  </xsl:otherwise>
                </xsl:choose>
              </xsl:variable>
							
							<xsl:element name="td">
								<xsl:attribute name="id">
									<xsl:value-of select="$id_base" />r<xsl:value-of select="$row_number" />d<xsl:value-of select="$col_number_set2" /><xsl:text>set2</xsl:text>
								</xsl:attribute>
								
								<xsl:if test="$ColorHighlighting='true'">
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="dedek:RGB(number(@val), number($color_norm_factor_set2))" />
                    <!--param. 2 byl $sum_of_values_set2-->
									</xsl:attribute>
								</xsl:if>
								
								<xsl:attribute name="border_right">
									<xsl:choose>
										<xsl:when test="position()=$pocet_kat_col"><xsl:value-of select="$bord_out"/></xsl:when>
										<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
									</xsl:choose>
								</xsl:attribute>
								<xsl:attribute name="border_bottom">
									<xsl:choose>
										<xsl:when test="$row_number=$pocet_kat_row"><xsl:value-of select="$bord_out"/></xsl:when>
										<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
									</xsl:choose>
								</xsl:attribute>
								
								<text id="{$id_base}r{$row_number}d{$col_number_set2}textset2">
									<xsl:value-of select="dedek:normalize_value(number(@val),number($norm_factor_set2))"/>
								</text> 
							</xsl:element>	
							
						</xsl:for-each>
						
						<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
								<xsl:element name="td">
									<xsl:attribute name="id">
										<xsl:value-of select="$id_base"/>r<xsl:value-of select="$row_number"/><xsl:text>d_sumset2</xsl:text>
									</xsl:attribute>
									
									<!--kody - policka se souctem se nehighlightuji 
                  <xsl:if test="$ColorHighlighting='true'">
										<xsl:attribute name="bgcolor">
											<xsl:value-of select="dedek:RGB(number($row_values_sum_set2), number($sum_of_values_set2))" />
										</xsl:attribute>
									</xsl:if>-->
									
									<xsl:attribute name="border_left"><xsl:value-of select="$bord_frm"/></xsl:attribute>
									<xsl:attribute name="border_right"><xsl:value-of select="$bord_out"/></xsl:attribute>
									<xsl:attribute name="border_bottom">
										<xsl:choose>
											<xsl:when test="$row_number=$pocet_kat_row"><xsl:value-of select="$bord_out"/></xsl:when>
											<xsl:otherwise><xsl:value-of select="$bord_in"/></xsl:otherwise>
										</xsl:choose>
									</xsl:attribute>
									
									<text id="{$id_base}r{$row_number}d_sum_textset2">
										<xsl:value-of select="$row_values_sum_set2" />
									</text>
								</xsl:element>
						</xsl:if>
						
					  </xsl:if>  <!-- Second set show-->
					  
					  
						
					</tr>
					
				</xsl:for-each>
				
				
				<!-- last row of table (sum of values) -->
				<!-- Kody - trochu prasecina, ale lip asi nejde. Pomoci klice hypotezy. -->
				
				<xsl:if test="$SumShow='true' and $TypeOfValues='abs'">
					<tr id="{$id_base}r_sum">
					  
					  <xsl:if test="$FirstSetShow='true'">
					
						<td id="{$id_base}r_sum_d0_set1" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_frm}" border_bottom="{$bord_out}">
							<text id="{$id_base}r_sum_d0text_set1"><xsl:value-of select="$label_sum" /></text>
						</td>
				
						<xsl:for-each select="tab[position()=1]/r[position()=1]/c">
							<xsl:variable name="col_number_set1" select="position()" />	
							<xsl:variable name="sum_of_column_set1" select="sum(key('key_hyp_sdkl',$hyp_id)/tab[position()=1]/r/c[position()=$col_number_set1]/@val)" />
						
							<xsl:element name="td">
								<xsl:attribute name="id">
									<xsl:value-of select="$id_base" />r_sum_d<xsl:value-of select="$col_number_set1" /><xsl:text>_set1</xsl:text>
								</xsl:attribute>
								
								<!--kody - policka se souctem se nehighlightuji 
                <xsl:if test="$ColorHighlighting='true'">
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="dedek:RGB(number($sum_of_column_set1), number($sum_of_values_set1))" />
									</xsl:attribute>
								</xsl:if>-->
								
								<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>
								<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
								<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
								
								<text id="{$id_base}r_sum_d{$col_number_set1}text_set1">
									<xsl:value-of select="$sum_of_column_set1"/>
								</text>
							</xsl:element>
					
						</xsl:for-each>
						
						<td id="{$id_base}r_sum_d_total_sum_set1" border_left="{$bord_frm}" border_right="{$bord_out}" border_top="{$bord_frm}" border_bottom="{$bord_out}">
								<text id="{$id_base}r_sum_d_total_sum_text_set1">
									<xsl:value-of select="$sum_of_values_set1" />
								</text>
						</td>
					    <xsl:if test="$SecondSetShow='true'">
							<td id="{$id_base}rsum_mezera_set1"/>
						</xsl:if>
					    
					  </xsl:if> <!-- First set show-->
					  
					  
					  
					  
					  <xsl:if test="$SecondSetShow='true'">
					  	
					  	<td id="{$id_base}r_sum_d0_set2" bgcolor="{$border_color}" border_left="{$bord_out}" border_right="{$bord_frm}" border_top="{$bord_frm}" border_bottom="{$bord_out}">
							<text id="{$id_base}r_sum_d0text_set2"><xsl:value-of select="$label_sum" /></text>
						</td>
				
						<xsl:for-each select="tab[position()=2]/r[position()=1]/c">
							<xsl:variable name="col_number_set2" select="position()" />	
							<xsl:variable name="sum_of_column_set2" select="sum(key('key_hyp_sdkl',$hyp_id)/tab[position()=2]/r/c[position()=$col_number_set2]/@val)" />
						
							<xsl:element name="td">
								<xsl:attribute name="id">
									<xsl:value-of select="$id_base" />r_sum_d<xsl:value-of select="$col_number_set2" /><xsl:text>_set2</xsl:text>
								</xsl:attribute>
								
								<!--kody - policka se souctem se nehighlightuji 
                <xsl:if test="$ColorHighlighting='true'">
									<xsl:attribute name="bgcolor">
										<xsl:value-of select="dedek:RGB(number($sum_of_column_set2), number($sum_of_values_set2))" />
									</xsl:attribute>
								</xsl:if>-->
								
								<xsl:attribute name="border_top"><xsl:value-of select="$bord_frm"/></xsl:attribute>
								<xsl:attribute name="border_right"><xsl:value-of select="$bord_in"/></xsl:attribute>
								<xsl:attribute name="border_bottom"><xsl:value-of select="$bord_out"/></xsl:attribute>
								
								<text id="{$id_base}r_sum_d{$col_number_set2}text_set2">
									<xsl:value-of select="$sum_of_column_set2"/>
								</text>
							</xsl:element>
					
						</xsl:for-each>
						
						<td id="{$id_base}r_sum_d_total_sum_set2" border_left="{$bord_frm}" border_right="{$bord_out}" border_top="{$bord_frm}" border_bottom="{$bord_out}">
								<text id="{$id_base}r_sum_d_total_sum_text_set2">
									<xsl:value-of select="$sum_of_values_set2" />
								</text>
						</td>
					    <xsl:if test="$SecondSetShow='true'">
							<td id="{$id_base}rsum_mezera_set2"/>
						</xsl:if>
					  	
					  </xsl:if>
					
					</tr>
					
				</xsl:if>
				
				
			</xsl:element>
			
			
			
			<!-- Show table legend-->
			<xsl:if test="$ShowLegend='true'">
				<text id="{$id_base}title"><br/><xsl:value-of select="$TabLegend"/><br/></text> 
			</xsl:if>

				
		</paragraph>


	</xsl:if>

</xsl:template>
	




</xsl:stylesheet>
