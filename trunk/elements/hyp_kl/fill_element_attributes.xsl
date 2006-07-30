<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
    
    
    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>

    
    <!-- definovani klice - dulezite kvuli hledani elementu s danym ID v celem dokumentu -->
    <xsl:key name="attribute_id" match="ti_attribute" use="@id" />
    
          
	
	<xsl:template match="hyp_kl">
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
				<!-- vygenerovani atributu -->
				
				<xsl:apply-templates select="@*"/>

				<!-- vygenerovani hodnot kontingencni tabulky -->
				
				
				<xsl:variable name="kategorie_radek" >	
					<xsl:value-of select="@row_attributes" />
				</xsl:variable>
				
				<xsl:variable name="kategorie_sloupec">
					<xsl:value-of select="@column_attributes" />
				</xsl:variable>
				
				
				<xsl:for-each select="tab/r" > <!-- cyklus pres radky-->
				   <xsl:variable name="cislo_radku" select="position()" />
				   
				   <xsl:for-each select="c">  <!-- cyklus pres polozky radku-->
				   		<xsl:variable name="cislo_sloupce" select="position()" />
				   		<xsl:variable name="jmeno" >
				   				<xsl:text>Tab1(</xsl:text>
				   				<xsl:value-of select="key('attribute_id' , $kategorie_radek)/ti_category[$cislo_radku]/@value" />
				   								   				
				   				<xsl:text>;</xsl:text>
				   				
				   				<xsl:value-of select="key('attribute_id' , $kategorie_sloupec)/ti_category[$cislo_sloupce]/@value" />
				   				<xsl:text>)</xsl:text>
				   		</xsl:variable>
				   		
				   		<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
						<attribute name="{$jmeno}" value="{@val}" />
				   
				   </xsl:for-each>
				   
				</xsl:for-each>

				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>










	
	<!-- vypise vsechny atributy krome cedentu-->
	
	<xsl:template match="@*">
	
		
		<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				<xsl:when test="name()='sum'">
					<xsl:text>Sum</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='min'">
					<xsl:text>Min</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='max'">
					<xsl:text>Max</xsl:text>
				</xsl:when>
						
				
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jméno úlohy</xsl:text>
							</xsl:when>
							
							
							
							
							
							<xsl:when test="name()='chi_sq'">
								<xsl:text>ChiSq : Chi-kvadrát test</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_s'">
								<xsl:text>FncS : function-type KL-Quantifier (sum)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_r'">
								<xsl:text>FncR : function-type KL-Quantifier (row)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c'">
								<xsl:text>Nepodmíněná entropie H(C)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_r'">
								<xsl:text>Nepodmíněná entropie H(R)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c_r'">
								<xsl:text>Podmíněná entropie H(C|R)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='mi'">
								<xsl:text>Mutual information MI(C,R) normalizovaná</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='aic'">
								<xsl:text>Asymetrický informační koeficient AIC(R,C)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='kend'">
								<xsl:text>Kendallův coefficient</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
						
							
							<xsl:when test="name()='chi_sq'">
								<xsl:text>ChiSq : Chi-square test</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_s'">
								<xsl:text>FncS : function-type KL-Quantifier (sum)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='fnc_r'">
								<xsl:text>FncR : function-type KL-Quantifier (row)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c'">
								<xsl:text>Unconditional entropy H(C)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_r'">
								<xsl:text>Unconditional entropy H(R)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='h_c_r'">
								<xsl:text>Conditional entropy H(C|R)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='mi'">
								<xsl:text>Mutual information MI(C,R) normalized</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='aic'">
								<xsl:text>Asymetric information coefficient AIC(R,C)</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='kend'">
								<xsl:text>Kendall coefficient</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->

		
		
					<attribute name="{name()}" value="{.}" label="{$label}" />
	</xsl:template>
	
	








	<!-- zpracovani cedentu-->
	
	<xsl:template match="@row_attributes | @column_attributes | @condition">
		
		<xsl:apply-templates select="id(.)" mode="values" />		

	</xsl:template>
	
	
	
	<xsl:template name="categorial_cedent">
			<attribute name="{@type}" value="{@quant}" />	

	</xsl:template>
	

	<!-- boolske literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:variable name="hodnota_cedentu">
    		<xsl:apply-templates select="ti_literal" mode="values"/>
    	</xsl:variable>
    	<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{@type}" value="{$hodnota_cedentu}" />	
	</xsl:template>
	
	
	
	<!-- kategorialni cedent -->
	<xsl:template match="ti_attribute" mode="values">
		<xsl:text disable-output-escaping="yes">
					</xsl:text>		
    	<attribute name="{@type}" value="{@quant}" />
	</xsl:template>
	

	<!-- preformatuje boolsky literal -->
	<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
	</xsl:template>
	






</xsl:stylesheet>
